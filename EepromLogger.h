/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __EEPROMLOGGER_H__
#define __EEPROMLOGGER_H__

// STL includes
// C includes
// Library includes
#include <SimpleLogger.h>

// Project includes
#include <EepromStream.h>

/**
 * Logs Tictocs events to EEPROM.
 *
 * This is a general-purpose library, which could be abstracted out to the 
 * Tictocs library.  Doing so would require solving the RTC mess, and
 * bringing EepromStream with it.
 *
 * @todo Abstract out to Tictocs library
 * @todo Better separate protocol details from logic
 */

class EepromLogger: public SimpleLogger
{
public:
  typedef uint8_t val1_t;
private:
  EepromStream eep;
  uint8_t overflow;
  uint32_t marked_time;
protected:
  virtual void log_emit(const Connectable* object, uint8_t signal);
  virtual void log_notify(const Connectable* object);
  void write_begin(void);
  void write_end(void);
  void write_marktime(void); 
  void write_time(void);
  uint32_t decode_time_value(val1_t val) const;
  prog_char* decode_object(val1_t) const;
  prog_char* decode_signal(val1_t) const;
  prog_char* lookup_object(uint8_t) const;
  prog_char* lookup_signal(uint8_t) const;
  void fast_forward(void);
  void playback(EepromStream& player, bool print);
  template <class T> void write(const T& t)
  {
    // cache our own overflow over multiple writes
    eep.write(t);
    overflow = overflow || eep.didOverflow();
  }

public:
  EepromLogger(void): SimpleLogger(32,32), overflow(false), marked_time(0) {}
  void begin(void);
  void play(void);
  void clear(void);
};

#endif // __EEPROMLOGGER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
