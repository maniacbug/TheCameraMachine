/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

// STL includes
// C includes
// Library includes
// Project includes
#include <EepromLogger.h>

/****************************************************************************/

// Protocol Layer

typedef EepromLogger::val1_t val1_t;
static const int num_type_bits = 2;
static const int type_shift = 8 - num_type_bits;
static const val1_t type_mask = (val1_t)((val1_t)(-1) << type_shift); 
static const val1_t value_mask = (val1_t)(~type_mask);

static const int type_command = 0;
static const int type_notify = 1;
static const int type_time = 2;
static const int type_emit = 3;

static const int command_begin = 1;
static const int command_end = 2;

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

prog_char* EepromLogger::decode_signal(uint8_t val) const
{
  prog_char* result = PSTR("Unknown");
  
  uint8_t signal_index = val & (0xFF >> 2);
  
  prog_char* lookup = signal_at(signal_index);
  if (lookup)
    result = lookup;

  return result;
}

/****************************************************************************/

static bool play_command(int command)
{
  bool done = false;

  switch (command)
  {
  case command_begin:
    printf_P(PSTR("LOG  BEGIN\n\r"));
    break;
  case command_end:
    printf_P(PSTR("LOG  END\n\r"));
    done = true;
    break;
  default:
    printf_P(PSTR("Unknown command %u"),command);
    done = true;
    break;
  };

  return done;
}

/****************************************************************************/

void EepromLogger::write_end(void) 
{
  eep.write(make_command(command_end));
  eep.seek(eep.tell() - sizeof(val1_t));
}
/****************************************************************************/

void EepromLogger::begin(void) 
{
  eep.write(make_command(command_begin));
  write_end();
}

/****************************************************************************/

void EepromLogger::play(void) const 
{
  printf_P(PSTR("LOG  *** Begin Log Playback\n\r"));

  EepromStream player;
  val1_t val1;
  uint8_t byte2;

  bool done = false;
  while (!done)
  {
    player.read(val1);
    switch ( val1 >> type_shift )
    {
    case type_emit:
      player.read(byte2);
      printf_P(PSTR("LOG  EMIT %S %S"),decode_object(val1),decode_signal(byte2));
      break;
    case type_notify:
      printf_P(PSTR("LOG  NOTF %S"),decode_object(val1));
      break;
    case type_time:
      printf_P(PSTR("LOG  Unknown value %u"),val1);
      break;
    case type_command:
      done = play_command(val1 & value_mask);
      break;
    default:
      printf_P(PSTR("LOG  Unknown value %u"),val1);
      done = true;
      break;
    }
  }
}

/****************************************************************************/

void EepromLogger::log_emit(const Connectable* object, uint8_t signal)
{
  SimpleLogger::log_emit(object,signal);

  eep.write(make_emit_1(find_index(object)));
  eep.write(make_emit_2(find_index(signal)));
  write_end();
}

/****************************************************************************/

void EepromLogger::log_notify(const Connectable* object)
{
  SimpleLogger::log_notify(object);

  eep.write(make_notify(find_index(object)));
  write_end();
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp
