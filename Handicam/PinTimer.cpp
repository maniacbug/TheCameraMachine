/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

// STL headers
// C headers
// Framework headers
// Library headers
#include <Updater.h>
// Project headers
// This component's header
#include "PinTimer.h"

/****************************************************************************/

PinTimer::PinTimer(Connector& _conn,int _pin,uint8_t _signal_low,
    uint8_t _signal_high,unsigned long _interval):
  PinControl(_conn,_pin,_signal_low,_signal_high),
  Tictocs::Timer(_interval)
{
  disable();
}
/****************************************************************************/

void PinTimer::begin(Updater& up,Connectable* who) 
{ 
  PinControl::begin(who);
  up.add(this);
}

/****************************************************************************/

void PinTimer::onFired(void)
{
  digitalWrite(get_pin(),digitalRead(get_pin())^HIGH);
  disable();
}

/****************************************************************************/

void PinTimer::onNotify(const Connectable* who, uint8_t signal)
{
  PinControl::onNotify(who,signal);
  reset();
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp
