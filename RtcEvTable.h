
/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __RTCEVTABLE_H__
#define __RTCEVTABLE_H__

// STL includes
// C includes
// Library includes
#include <Connector.h>
#include <IUpdate.h>
// Project includes

/**
 * Maintains a list of time values and a signal to emit.  Monitors RTC time
 * and emits the signal when the time for each passes.
 *
 * This is currently application-specific only because it relies on the
 * logger by name.  This is not needed.  It could rely on a SimpleLibrary*.
 * Or even a 'dictionary' interface.
 */

class RtcEvTable: public Connectable, public IUpdate
{
public:
  typedef prog_uint8_t evline[7];
private:
  evline* table;
  evline* current;
  uint8_t num_lines;
protected:
  void update(void);
  bool is_valid(void) const;
public:
  RtcEvTable(Connector& _conn,evline*,uint8_t);
  void begin(void);
  void reset(void) { current = table; }
  uint32_t whenNext(void) const;
};

#endif // __RTCEVTABLE_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
