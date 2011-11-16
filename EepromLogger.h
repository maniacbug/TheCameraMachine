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
#include <RtcEvent.h>

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
  const IRtc* rtc;
  uint32_t marked_time;
  uint32_t last_time;
protected:
  virtual void log_emit(const Connectable* object, uint8_t signal);
  virtual void log_notify(const Connectable* object);
  void write_end(void);
  void write_marktime(void); 
  void write_time(void);
  prog_char* decode_object(val1_t) const;
  prog_char* decode_signal(uint8_t) const;
  uint32_t decode_time_value(val1_t val) const;
  void fast_forward(void);
  bool play_command(EepromStream&,unsigned at,int command) const;
  bool fast_forward_command(int command);
  template <class T> void write(const T& t)
  {
    // cache our own overflow over multiple writes
    eep.write(t);
    overflow = overflow || eep.didOverflow();
  }

public:
  EepromLogger(void): SimpleLogger(32,32), overflow(false), rtc(NULL), marked_time(0) {}
  void begin();
  void play() const;
  void setRtc(const IRtc* _rtc) 
  {
    rtc = _rtc;
  }
};

#endif // __EEPROMLOGGER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
