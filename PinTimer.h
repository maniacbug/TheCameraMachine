/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __PINTIMER_H__
#define __PINTIMER_H__

// STL headers
// C headers
// Framework headers
// Library headers
#include <TictocTimer.h>
#include <PinControl.h>
// Project headers

class Updater;

/**
 * Control a pin, and automatically set it back after a certain
 * interval
 */

class PinTimer: public PinControl, public Tictocs::Timer
{
private:
protected:
  virtual void onFired(void);
  virtual void onNotify(const Connectable* who, uint8_t signal);
public:
  PinTimer(Connector& _conn,int _pin,uint8_t _signal_low,uint8_t _signal_high,unsigned long _interval);
  void begin(Updater& up,Connectable* who);
};

#endif // __PINTIMER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
