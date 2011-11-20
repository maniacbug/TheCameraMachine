/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __SERIALLINEIN_H__
#define __SERIALLINEIN_H__

// STL includes
// C includes
// Library includes
#include <IUpdate.h>
#include <RtcEvent.h> // for IRtc
// Project includes

/**
 * Monitors serial input, compiles a line buffer, takes actions when the line
 * is full.
 *
 * This is not a general-purpose component, it relies on the objects defined
 * for this sketch, because it controls them.
 */

class SerialLineIn: public IUpdate
{
private:
  char buf[32];
  char* current;
  static IRtc* rtc;
protected:
  bool dispatch(void);
public:
  SerialLineIn(void);
  void update(void);
  static void setRtc(IRtc* _rtc)
  {
    rtc = _rtc;
  }
};
/****************************************************************************/

#endif // __SERIALLINEIN_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
