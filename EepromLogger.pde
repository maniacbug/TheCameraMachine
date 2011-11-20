/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

// STL includes
// C includes
// Library includes
#include <RTClib.h>
// Project includes
#include <EepromLogger.h>

/****************************************************************************/

// Protocol Layer

typedef EepromLogger::val1_t val1_t;
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

static inline val1_t make_command(int command)
{
  return (type_command << type_shift ) | ( command & value_mask );
}

static inline val1_t make_emit_1(int index)
{
  return (type_emit << type_shift ) | ( index & value_mask );
}

static inline uint8_t make_emit_2(int index)
{
  return index & (0xFF >> 2);
}

static inline val1_t make_notify(int index)
{
  return (type_notify << type_shift ) | ( index & value_mask );
}

static inline val1_t make_time(uint32_t time_value)
{
  return (type_time << type_shift ) | ( ( time_value >> time_shift ) & value_mask );
}

/****************************************************************************/

uint32_t EepromLogger::decode_time_value(val1_t val) const
{
  return ( ( val & value_mask ) << time_shift ) + marked_time;
}

/****************************************************************************/

prog_char* EepromLogger::decode_object(val1_t val) const
{
  prog_char* result = PSTR("Unknown");

  uint8_t object_index = val & value_mask;

  prog_char* lookup = object_at(object_index);
  if (lookup)
    result = lookup;

  return result;
}

/****************************************************************************/

prog_char* EepromLogger::decode_signal(val1_t val) const
{
  prog_char* result = PSTR("Unknown");
  
  uint8_t signal_index = val & (0xFF >> 2);
  
  prog_char* lookup = signal_at(signal_index);
  if (lookup)
    result = lookup;

  return result;
}

/****************************************************************************/

// This is really kind of a mess :(
bool EepromLogger::fast_forward_command(int command)
{
  bool done = false;
  uint32_t now;

  switch (command)
  {
  case command_begin:
  case command_overflow:
    break;
  case command_marktime:
    eep.read(now);
    marked_time = now;
    break;
  case command_end:
    done = true;
    break;
  default:
    done = true;
    break;
  };

  return done;
}
/****************************************************************************/

bool EepromLogger::play_command(EepromStream& stream,unsigned at,int command)
{
  bool done = false;
  uint32_t now;
  char buf[32];

  switch (command)
  {
  case command_begin:
    printf_P(PSTR("LOG  %04u BEGIN\n\r"),at);
    break;
  case command_end:
    printf_P(PSTR("LOG  %04u END\n\r"),at);
    done = true;
    break;
  case command_overflow:
    printf_P(PSTR("LOG  %04u RESTARTED due to EEPROM overflow\n\r"),at);
    break;
  case command_marktime:
    stream.read(now);
    marked_time = now;
    printf_P(PSTR("LOG  %04u MARK TIME %s\n\r"),at,DateTime(now).toString(buf,sizeof(buf)));
    break;
  default:
    printf_P(PSTR("LOG  %04u Unknown command %u"),at,command);
    done = true;
    break;
  };

  return done;
}

/****************************************************************************/

void EepromLogger::write_end(void) 
{
  write(make_command(command_end));
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
    write(make_command(command_begin));
    write(make_command(command_overflow));
    write_time();
    write(make_command(command_end));
    eep.seek(eep.tell() - sizeof(val1_t));

  }
}

/****************************************************************************/

void EepromLogger::write_time(void) 
{
  if ( rtc )
  {
    uint32_t now = rtc->now_unixtime();
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
	write(make_time(marked_diff));
      }
    }
    // Otherwise, write a mark time
    else
      write_marktime();
  }
}

/****************************************************************************/

void EepromLogger::write_marktime(void) 
{
  marked_time = rtc->now_unixtime();
  write(make_command(command_marktime));
  write(marked_time);
}

/****************************************************************************/

void EepromLogger::begin(void) 
{
  // Reset the eeprom stream
  eep.seek(0);

  // First, seek to find the end of the existing logs, only applicable if
  // the first byte is a 'begin'
  val1_t at0;
  eep.peek(at0);
  if ( at0 == make_command(command_begin) )
  {
    //play();
    fast_forward();
  }

  // Then write the begin/end for the current run
  val1_t begin = make_command(command_begin);
  val1_t first = 0;
  unsigned pos = eep.tell();
  if ( pos > 0 )
  {
    eep.seek(pos-1);
    eep.read(first);
  }
  if ( first != begin )
    write(begin);
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
  write(make_command(command_begin));
  write_end();
}

/****************************************************************************/

void EepromLogger::fast_forward(void)
{
  val1_t val1;
  uint8_t byte2;

  bool done = false;
  while (!done)
  {
    eep.read(val1);
    if ( eep.didOverflow() )
    {
      eep.seek(1);
      break;
    }
    
    switch ( val1 >> type_shift )
    {
    case type_emit:
      eep.read(byte2);
      break;
    case type_notify:
      break;
    case type_time:
      marked_time = decode_time_value(val1);
      break;
    case type_command:
      done = fast_forward_command(val1 & value_mask);
      break;
    default:
      done = true;
      break;
    }
  }
  eep.seek(eep.tell()-1);
}

/****************************************************************************/

void EepromLogger::play(void)
{
  printf_P(PSTR("LOG  **** Begin Log Playback\n\r"));

  EepromStream player;
  val1_t val1;
  uint8_t byte2;
  char buf[32];

  bool done = false;
  while (!done)
  {
    unsigned at = player.tell();
    player.read(val1);
    if ( player.didOverflow() )
      break; 

    switch ( val1 >> type_shift )
    {
    case type_emit:
      player.read(byte2);
      printf_P(PSTR("LOG  %04u EMIT %S %u %S %u\n\r"),at,decode_object(val1),val1&value_mask,decode_signal(byte2),byte2);
      break;
    case type_notify:
      printf_P(PSTR("LOG  %04u NOTF %S %u\n\r"),at,decode_object(val1),val1&value_mask);
      break;
    case type_time:
      marked_time = decode_time_value(val1);
      printf_P(PSTR("LOG  %04u TIME %s\n\r"),at,DateTime(marked_time).toString(buf,sizeof(buf)));
      break;
    case type_command:
      done = play_command(player,at,val1 & value_mask);
      break;
    default:
      printf_P(PSTR("LOG  %04u Unknown value %u\n\r"),at,val1);
      done = true;
      break;
    }
  }
}

/****************************************************************************/

void EepromLogger::log_emit(const Connectable* object, uint8_t signal)
{
  SimpleLogger::log_emit(object,signal);

  write_time();
  write(make_emit_1(find_index(object)));
  write(make_emit_2(find_index(signal)));
  write_end();
}

/****************************************************************************/

void EepromLogger::log_notify(const Connectable* object)
{
  SimpleLogger::log_notify(object);

  write_time();
  write(make_notify(find_index(object)));
  write_end();
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp
