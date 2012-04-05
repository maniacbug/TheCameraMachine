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
// Framework includes
#include <EEPROM.h>
// Library includes
// Project includes

/**
 * Turns the EEPROM into one big read/writeable stream.  Makes it simple to
 * read or write any object.
 *
 * This is a general-purpose class, and could be abstracted out into its own
 * library.
 *
 * @todo Could implement the Print class
 */

class EepromStream
{
private:
  unsigned start_address;
  unsigned current_address; // As an offset from start_address
  unsigned end_address; // As an offset from start_address
  bool overflow;
protected:
  // Handle wrapping the address around the end
  unsigned next(unsigned& current)
  {
    unsigned result = current++;
    while ( current >= end_address )
    {
      current -= end_address;
      overflow = true;
    }
    return result;
  }
public:
  EepromStream(unsigned starts_at = 0, unsigned length = 1024): 
    start_address(starts_at), current_address(0), end_address(length), 
    overflow(false) 
  {}
  template <class T> void write(const T& object) 
  {
    overflow = false;
    int i = sizeof(T);
    const uint8_t* current = reinterpret_cast<const uint8_t*>(&object);
    while (i--)
      EEPROM.write(start_address + next(current_address),*current++);
  }
  template <class T> void read(T& object)
  {
    overflow = false;
    int i = sizeof(T);
    uint8_t* current = reinterpret_cast<uint8_t*>(&object);
    while (i--)
      *current++ = EEPROM.read(start_address + next(current_address));
  }
  template <class T> void peek(T& object)
  {
    overflow = false;
    unsigned address = current_address;
    int i = sizeof(T);
    uint8_t* current = reinterpret_cast<uint8_t*>(&object);
    while (i--)
      *current++ = EEPROM.read(start_address + next(address));
  }
  void seek( unsigned to )
  {
    current_address = to;
    while ( current_address >= end_address )
      current_address -= end_address;
  }
  unsigned tell( void ) const
  {
    return current_address;
  }
  bool didOverflow( void ) const
  {
    return overflow;
  }
};

#endif // __EEPROMSTREAM_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
