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
#include <MemoryFree.h>
#include <Updater.h>
// Project includes
#include "SerialLineIn.h"
#include "objects.h"

/****************************************************************************/

inline uint8_t conv2d(const char* p)
{
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9')
        v = *p - '0';
    return 10 * v + *++p - '0';
}

void print_time(void)
{
  char buf[32];
  RTC.nowDateTime().toString(buf,sizeof(buf));
  printf_P(PSTR("RTC  The time is now %s\n\r"),buf);
}

/****************************************************************************/

SerialLineIn::SerialLineIn(void): current(buf)
{
}

/****************************************************************************/

void SerialLineIn::begin(Updater& up)
{
  up.add(this);
}

/****************************************************************************/

bool SerialLineIn::dispatch(void) 
{
  bool handled = false;
  DateTime now = RTC.nowDateTime();
  switch (toupper(*buf))
  {
    case 'D':
      // Dyymmdd: Set date
      handled = true;
      if ( strlen(buf) == 1 )
      {
	print_time();
	break;
      }
      if ( strlen(buf) != 7 )
      {
	printf_P(PSTR("SERL Format: Dyymmdd\n\r"));
	break;
      }
      now = DateTime(2000+conv2d(buf+1),conv2d(buf+3),conv2d(buf+5),now.hour(),now.minute(),now.second());
      RTC.adjust(now);
      print_time();
      break;
    case 'T':
      // Thhmmss: Set time
      handled = true;
      if ( strlen(buf) != 7 )
      {
	printf_P(PSTR("SERL Format: Dyymmdd\n\r"));
	break;
      }
      now = DateTime(now.year(),now.month(),now.day(),conv2d(buf+1),conv2d(buf+3),conv2d(buf+5));
      RTC.adjust(now);
      print_time();
      break;
    case '@':
      handled = true;
      // Special time values

      if ( !strcmp(buf+1,"N") )
      {
	uint32_t when = events.whenNext();
#ifdef HAVE_FIRE_CAMERA
	if ( fire_camera.is_valid() )
	  when = fire_camera.whenNext();
#endif
	RTC.adjust(when);
	print_time();
      }
      else if ( !strcmp(buf+1,"1") )
      {
	events.reset();
#ifdef HAVE_FIRE_CAMERA
	fire_camera.invalidate();
#endif
	RTC.adjust(events.whenNext());
	print_time();
      }
      else if ( !strcmp(buf+1,"0") )
      {
	RTC.adjust(DateTime(2011,1,1,0,0,0).unixtime());
	print_time();
      }
      else
	printf_P(PSTR("SERL Error: Unknown @ value: %s"),buf+1);
      break;
    case 'E':
      // E: Print EEPROM
      handled = true;
      logger.play();

      break;
    case 'F':
      // F: Free memory 
      handled = true;
      printf_P(PSTR("FREE %u\n\r"),freeMemory());

      break;
  }
  return handled;
}

/****************************************************************************/

void SerialLineIn::update(void) 
{
  while ( Serial.available() )
  {
    char c = Serial.read();
    Serial.print(c);
    if ( c != '\n' && c != '\r' )
      *current++ = c;
    
    if ( current >= buf + sizeof(buf) - 1 || c == '\n' || c == '\r' )
    {
      *current = 0;
      bool handled = dispatch();
      current = buf;

      if ( ! handled )
	printf_P(PSTR("SERL Error: Command not found."));
    }
  }
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp
