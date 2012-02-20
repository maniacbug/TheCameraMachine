/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

// STL includes
// C includes
// Framework includes
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
// Library includes
#include <AnyRtc.h>
// Project includes
#include "EepromLogger.h"

/****************************************************************************/
/****************************************************************************/

/* PROTOCOL LAYER: The only things that know the bit ordering of the protocol */ 

/****************************************************************************/
/****************************************************************************/

/**
 * Protocol description
 *
 * Byte #1: d6-7: type (see type_xxx)
 *          d0-5: value
 *
 * Value for type_command; See command_xxxx
 *       for type_notify: Object index into dictionary
 *       for type_emit: Object index into dictionary
 *       for type_time: Time offset, shifted right by time_shift 
 *
 * Following for command_marktime: uint32_t unix time stamp
 *           for type_emit: d0-5: Signal index into dictionary
 *                          d6-7: Reserved
 */

/****************************************************************************/

// Constants & Simple Types 

typedef uint8_t val1_t;
static const int num_type_bits = 2;
static const int type_shift = 8*sizeof(val1_t) - num_type_bits;
static const val1_t type_mask = (val1_t)((val1_t)(-1) << type_shift); 
static const val1_t value_mask = (val1_t)(~type_mask);
static const int time_shift = 3;
static const val1_t min_time_diff = 1 << time_shift;
static const uint32_t max_time_diff = (uint32_t)value_mask << time_shift;

static const int type_command = 0;
static const int type_notify = 1;
static const int type_time = 2;
static const int type_emit = 3;

static const int command_begin = 1;
static const int command_end = 2;
static const int command_overflow = 3;
static const int command_marktime = 4;

/****************************************************************************/

// Protocol Types 

// Each type contains the in-EEPROM representation of the logged data, and
// has the responsibility to create that representation from original data
// or extract the original data from the representation.

struct command_t
{
  val1_t v1;
  command_t(void): v1(0)
  {
  }
  command_t(int command)
  {
    v1 = (type_command << type_shift ) | ( command & value_mask );
  }
  bool operator==(const command_t& _rhs) const { return v1 == _rhs.v1; }
  bool operator!=(const command_t& _rhs) const { return v1 != _rhs.v1; }
};

struct begin_t: command_t
{
  begin_t(void): command_t(command_begin) {}
};

struct end_t: command_t
{
  end_t(void): command_t(command_end) {}
};

struct overflow_t: command_t
{
  overflow_t(void): command_t(command_overflow) {}
};

struct marktime_t: command_t
{
  uint32_t tval;
  marktime_t(void): command_t(command_marktime) { tval = -1; }
  marktime_t(uint32_t _tval): command_t(command_marktime), tval(_tval) {}
  uint32_t time(void) const { return tval; }
} __attribute__ ((packed));

struct notify_t
{
  val1_t v1;
  notify_t(void)
  {
    v1 = (type_notify << type_shift ) | ( 0xFF & value_mask );
  }
  notify_t(int object_index)
  {
    v1 = (type_notify << type_shift ) | ( object_index & value_mask );
  }
  int object_index(void) const
  {
    return v1 & value_mask;
  }
};

struct emit_t 
{
  val1_t v1;
  uint8_t v2;
  emit_t(void)
  {
    v1 = (type_emit << type_shift ) | ( 0xff & value_mask );
    v2 = 0xff;
  }
  emit_t(int object_index, int signal_index)
  {
    v1 = (type_emit << type_shift ) | ( object_index & value_mask );
    v2 = signal_index & (0xFF >> 2);
  }
  int object_index(void) const
  {
    return v1 & value_mask;
  }
  int signal_index(void) const
  {
    return v2 & (0xFF >> 2);
  }
};

struct reltime_t
{
  val1_t v1;
  reltime_t(void)
  {
    v1 = (type_time << type_shift ) | ( 0xff & value_mask );
  }
  reltime_t(uint32_t time_value)
  {
    v1 = (type_time << type_shift ) | ( ( time_value >> time_shift ) & value_mask );
  }
  uint32_t time_value(void) const
  {
    return (v1 & value_mask) << time_shift;
  }
};

template <class T>
bool is_type(const T& t,val1_t v)
{
  return (t.v1 & type_mask) == (v & type_mask);
}

template <class T>
bool is_command(const T& t,val1_t v)
{
  return t.v1 == v; 
}

/****************************************************************************/

const char* EepromLogger::lookup_object(uint8_t object_index) const
{
  const char* result = PSTR("Unknown");

  const char* lookup = object_at(object_index);
  if (lookup)
    result = lookup;

  return result;
}

/****************************************************************************/

const char* EepromLogger::lookup_signal(uint8_t signal_index) const
{
  const char* result = PSTR("Unknown");
  
  const char* lookup = signal_at(signal_index);
  if (lookup)
    result = lookup;

  return result;
}

/****************************************************************************/
/****************************************************************************/

/* PLAYBACK: Things which read from the log */ 

/****************************************************************************/
/****************************************************************************/

/****************************************************************************/

void EepromLogger::playback(EepromStream& player, bool print)
{
  if (print) printf_P(PSTR("LOG  **** Begin Log Playback\n\r"));

  val1_t current; 
  char buf[32];

  bool done = false;
  while (!done)
  {
    unsigned at = player.tell();
    player.peek(current);
    done =  player.didOverflow();

    if ( is_type(command_t(0),current) )
    {
      if ( is_command(begin_t(),current) )
      {
	begin_t x;
	player.read(x);
	if (print) printf_P(PSTR("LOG  %04u BEGIN\n\r"),at);
      }
      else if ( is_command(end_t(),current) )
      {
	end_t x;
	player.read(x);
	if (print) printf_P(PSTR("LOG  %04u END\n\r"),at);
	done = true;
      }
      else if ( is_command(overflow_t(),current) )
      {
	overflow_t x;
	player.read(x);
	if (print) printf_P(PSTR("LOG  %04u RESTARTED due to EEPROM overflow\n\r"),at);
      }
      else if ( is_command(marktime_t(),current) )
      {
	marktime_t x;
	player.read(x);
	marked_time = x.time();
	if (print) printf_P(PSTR("LOG  %04u MARK TIME %s\n\r"),at,DateTime(marked_time).toString(buf,sizeof(buf)));
      }
      else
      {
	player.read(current);
	if (print) printf_P(PSTR("LOG  %04u Unknown command %u"),at,current);
	done = true;
      }
    }
    else if ( is_type(notify_t(),current) )
    {
      notify_t x;
      player.read(x);
      if (print) printf_P(PSTR("LOG  %04u NOTF %S\n\r"),at,lookup_object(x.object_index()));
    }
    else if ( is_type(emit_t(),current))
    {
      emit_t x;
      player.read(x);
      if (print) printf_P(PSTR("LOG  %04u EMIT %S %S\n\r"),at,lookup_object(x.object_index()),lookup_signal(x.signal_index()));
    }
    else if ( is_type(reltime_t(),current))
    {
      reltime_t x;
      player.read(x);
      
      marked_time += x.time_value();
      if (print) printf_P(PSTR("LOG  %04u TIME %s\n\r"),at,DateTime(marked_time).toString(buf,sizeof(buf)));
    }
// This is impossible to get, because the entire bit space of types is covered by the
// valid types
#if 0
    else
    {
      player.read(current);
      if (print) printf_P(PSTR("LOG  %04u Unknown value %u\n\r"),at,current);
      done = true;
    }
#endif
  }
}

/****************************************************************************/

void EepromLogger::fast_forward(void)
{
  playback(eep,false);
  eep.seek(eep.tell()- sizeof(end_t));
}

/****************************************************************************/
void EepromLogger::play(void)
{
  EepromStream player;
  playback(player,true);
}

/****************************************************************************/
/****************************************************************************/

/* EXTERNAL SETUP */ 

/****************************************************************************/
/****************************************************************************/

/****************************************************************************/

void EepromLogger::begin(void) 
{
  // Reset the eeprom stream
  eep.seek(0);

  // First, seek to find the end of the existing logs, only applicable if
  // the first byte is a 'begin'
  const begin_t begin_marker;
  command_t current;
  eep.peek(current);
  if ( current == begin_marker ) 
  {
    //play();
    fast_forward();
  }

  // Then write the begin/end for the current run
  current = command_t();
  unsigned pos = eep.tell();
  if ( pos > 0 )
  {
    eep.seek(pos - sizeof(current));
    eep.read(current);
  }
  if ( current != begin_marker )
    write_begin();
  write_end();
}

/****************************************************************************/

void EepromLogger::clear(void) 
{
  // Reset the eeprom stream
  eep.seek(0);

  // Reset the reference time
  marked_time = 0;

  // Write the begin/end for the current run
  // Only if we're not already sitting on a begin
  write_begin();
  write_end();
}

/****************************************************************************/
/****************************************************************************/

/* LOGGERS: Things which write to the log */

/****************************************************************************/
/****************************************************************************/

/****************************************************************************/

void EepromLogger::write_time(void) 
{
  uint32_t now = RTC.now();
  uint32_t marked_diff = now - marked_time;

  // If we have a mark time and the time SINCE that mark time can be
  // represented in a val1...
  if ( marked_time && ( marked_diff < max_time_diff ) )
  {
    // If enough time has elapsed since the last time we wrote a time,
    // go ahead and write another -- otherwise don't bother
    if ( marked_diff > min_time_diff )
    {
      marked_time = now;
      write(reltime_t(marked_diff));
    }
  }
  // Otherwise, write a mark time
  else
    write_marktime();
}

/****************************************************************************/

void EepromLogger::write_marktime(void) 
{
  marked_time = RTC.now();
  write(marktime_t(marked_time));
}

/****************************************************************************/

void EepromLogger::write_begin(void) 
{
  write(begin_t());
}

/****************************************************************************/

void EepromLogger::write_end(void) 
{
  write(end_t());
  eep.seek(eep.tell() - sizeof(val1_t));

  // Manage overflow.  If the previous set of writes wrapped us around,
  // clear everything and start over.

  if (overflow)
  {
    overflow = false;
    
    // We've lost our time reference now, so the next write should write a
    // full time.
    marked_time = 0;

    eep.seek(0);
    write(begin_t());
    write(overflow_t());
    write_time();
    write(end_t());
    eep.seek(eep.tell() - sizeof(val1_t));
  }
}

/****************************************************************************/

void EepromLogger::log_emit(const Connectable* object, uint8_t signal)
{
  SimpleLogger::log_emit(object,signal);

  write_time();
  write(emit_t(find_index(object),find_index(signal)));
  write_end();
}

/****************************************************************************/

void EepromLogger::log_notify(const Connectable* object)
{
  SimpleLogger::log_notify(object);

  write_time();
  write(notify_t(find_index(object)));
  write_end();
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp
