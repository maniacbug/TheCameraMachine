/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

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

class Sequence: public Connectable, public Tictocs::Timer 
{
public:
  /**
   * Static structure which can be used to construct a sequence
   */
  struct Entry
  {
    uint32_t delayms; /**< MS to wait before emitting */
    uint8_t signal; /**< Signal to emit */
  };
private:
  const Entry* entries; /**< Current list of static entries, in flash */
  const Entry* current; /**< Current entry we're waiting for */
protected:
  /**
   * Event triggered when timer fires
   */
  virtual void onFired(void);

  /**
   * Whether this sequence has a valid current entry
   *
   * @return Whether the sequence has a valid current entry 
   */
  bool isValid(void) const;

  /**
   * Reset the interval and restart the timer, using the interval for the
   * current entry.
   */
  void resetInterval(void);
public:
  /**
   * Default constructor.  
   * 
   * @warning Adds no entries, so it will start in an invalid
   * (and inoperable state).  To use it, add entries later.  (Although you
   * can't now, so this constructor is kind of useless.)
   *
   * @param conn Connector used to emit our signals
   */
  Sequence(Connector& conn);
  /**
   * Fully-qualified constructor
   *
   * @param conn Connector used to emit our signals
   * @param entries Array of entries, in flash memory.  Terminated with a {0,0}.
   */
  Sequence(Connector& conn,const Entry*); 
};

#endif // __SEQUENCE_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
