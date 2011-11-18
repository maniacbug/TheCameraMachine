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
#include <SerialLineIn.h>

/****************************************************************************/

SerialLineIn::SerialLineIn(void): current(buf)
{
}

/****************************************************************************/

void SerialLineIn::dispatch(void) 
{
  switch (toupper(*buf))
  {
    case 'T':
      break;
    case 'E':
      break;
  }
}

/****************************************************************************/

void SerialLineIn::update(void) 
{
  if ( Serial.available() )
  {
    char c = Serial.read();
    Serial.print(c);
    if ( c != '\n' && c != '\r' )
      *current++ = c;
    
    if ( current >= buf + sizeof(buf) - 1 || c == '\n' || c == '\r' )
    {
      *current = 0;
      dispatch();
      current = buf;
    }
  }
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp
