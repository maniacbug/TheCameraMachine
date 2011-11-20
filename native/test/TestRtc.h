/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __TESTRTC_H__
#define __TESTRTC_H__

// STL includes
// C includes
// Library includes
#include <RtcEvent.h> // for IRtc
// Project includes

/**
 * Stupid RTC only used to test classes that need an RTC
 */

struct TestRtc: public IRtc
{
  uint32_t now;
  TestRtc(void): now(0) {}
  virtual bool is_after(uint32_t _time) const { return now > _time; }
  virtual void adjust(uint32_t _time) { now = _time; }
  virtual uint32_t now_unixtime(void) const { return now; }
};

#endif // __TESTRTC_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
