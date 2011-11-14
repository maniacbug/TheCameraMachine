/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __EEPROMSTREAM_H__
#define __EEPROMSTREAM_H__

// STL includes
// C includes
// Library includes
#include <EEPROM.h>

// Project includes

/**
 * Example for how classes should be declared
 */

class EepromStream
{
private:
  unsigned current_address;
protected:
public:
  EepromStream(void): current_address(0) {}
  template <class T> void write(const T& object) 
  {
    int i = sizeof(T);
    const uint8_t* current = reinterpret_cast<const uint8_t*>(&object);
    while (i--)
      EEPROM.write(current_address++,*current++);
  }
  template <class T> void read(T& object)
  {
    int i = sizeof(T);
    uint8_t* current = reinterpret_cast<uint8_t*>(&object);
    while (i--)
      *current++ = EEPROM.read(current_address++);
  }
  template <class T> void peek(T& object)
  {
    unsigned address = current_address;
    int i = sizeof(T);
    uint8_t* current = reinterpret_cast<uint8_t*>(&object);
    while (i--)
      *current++ = EEPROM.read(address++);
  }
  void seek( unsigned to )
  {
    current_address = to;
  }
  unsigned tell( void ) const
  {
    return current_address;
  }
};

#endif // __EEPROMSTREAM_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
