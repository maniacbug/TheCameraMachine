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
 * Example for how classes should be declared
 */

class EepromLogger: public SimpleLogger
{
public:
  typedef uint8_t val1_t;
private:
  EepromStream eep;
  bool overflow;
protected:
  virtual void log_emit(const Connectable* object, uint8_t signal);
  virtual void log_notify(const Connectable* object);
  void write_end(void);
  prog_char* decode_object(val1_t) const;
  prog_char* decode_signal(uint8_t) const;
  void fast_forward(void);
  template <class T> void write(const T& t)
  {
    // cache our own overflow over multiple writes
    eep.write(t);
    overflow = overflow || eep.didOverflow();
  }

public:
  EepromLogger(void): SimpleLogger(32,32), overflow(false) {}
  void begin();
  void play() const;
};

#endif // __EEPROMLOGGER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
