
/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __RTC_H__
#define __RTC_H__

// STL includes
// C includes
// Library includes
#include <RTClib.h>
#include <RtcEvent.h> // for IRtc
// Project includes

/**
 * Board-specific RTC.  Re-implemented for each different board.
 */

class BoardRtc: public IRtc
{
  uint32_t now;
public:
  void begin(void);
  bool is_after(uint32_t when) const; // { return now > when; }
  void adjust(uint32_t new_now);
  uint32_t now_unixtime(void) const;
};

#endif // __RTC_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
