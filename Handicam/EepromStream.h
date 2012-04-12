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
 * This is implemented in a header because it uses many templates to allow
 * users to serialize any class in/out of eeprom.
 *
 * @todo Could implement the Print class
 */

class EepromStream
{
private:
  unsigned start_address; /**< The first address in EEPROM which is managed by this stream */
  unsigned current_address; /**< The next address where a byte will be written, as an offset from start_address */ 
  unsigned end_address; /**< The first address beyond the area we manage, as an offset from start_address.  Also could be named 'length' */ 
  bool overflow;
protected:
  // Handle wrapping the address around the end
  /**
   * Increment and wrap the supplied address.  If the address would wrap,
   * reset it back to the beginning and set the overflow flag.
   *
   * @param [in/out] current The address to be incremented
   * @return The previous value of @p current
   */
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
  /**
   * Fully qualified constructor
   *
   * @param starts_at Where in the eeprom to place this stream
   * @param length How many bytes is the chunk of eeprom we manage
   */
  EepromStream(unsigned starts_at = 0, unsigned length = 1024): 
    start_address(starts_at), current_address(0), end_address(length), 
    overflow(false) 
  {}

  /**
   * Write an object to the stream
   *
   * @param object Object to write
   */
  template <class T> void write(const T& object) 
  {
    overflow = false;
    int i = sizeof(T);
    const uint8_t* current = reinterpret_cast<const uint8_t*>(&object);
    while (i--)
      EEPROM.write(start_address + next(current_address),*current++);
  }

  /**
   * Read an object from the stream
   *
   * @param [out] object Object to read in
   */
  template <class T> void read(T& object)
  {
    overflow = false;
    int i = sizeof(T);
    uint8_t* current = reinterpret_cast<uint8_t*>(&object);
    while (i--)
      *current++ = EEPROM.read(start_address + next(current_address));
  }
  /**
   * Peek at the next object in the stream
   *
   * Same as read(), but does not advance to the next address
   */
  template <class T> void peek(T& object)
  {
    overflow = false;
    unsigned address = current_address;
    int i = sizeof(T);
    uint8_t* current = reinterpret_cast<uint8_t*>(&object);
    while (i--)
      *current++ = EEPROM.read(start_address + next(address));
  }
  /**
   * Move the current address 
   *
   * @param to Location to seek
   */
  void seek( unsigned to )
  {
    current_address = to;
    while ( current_address >= end_address )
      current_address -= end_address;
  }

  /**
   * Retrieve the current address
   *
   * @return Current read/write address
   */
  unsigned tell( void ) const
  {
    return current_address;
  }

  /**
   * Whether the stream overflowed
   *
   * @return Whether an overflow was detected in the previous read(), write() or peek().
   */
  bool didOverflow( void ) const
  {
    return overflow;
  }
};

#endif // __EEPROMSTREAM_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
