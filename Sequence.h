/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

// STL headers
// C headers
// Framework headers
// Library headers
#include <TictocTimer.h>
// Project headers

/**
 * A sequence of signals which will be fired according to a timeline.
 *
 * It is a connectable timer that contains an array of delay/signal pairs.
 * The basic idea is to wait the delay for each, and then fire the signal.
 * Also, the sequence wakes up upon hearing its own wake-up signal.  It's
 * dormant until that.
 */

class Sequence: public Tictocs::Timer 
{
public:
  /**
   * Static structure which can be used to construct a sequence
   */
  struct Entry
  {
    uint32_t delayms;
    uint8_t signal;
  };
private:
protected:
public:
  Sequence(Entry*): Tictocs::Timer(0)
  {
    disable();

    // TODO: Do something with the entries
  }
  Sequence(void): Tictocs::Timer(0)
  {
    disable();
  }
};

#endif // __SEQUENCE_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
