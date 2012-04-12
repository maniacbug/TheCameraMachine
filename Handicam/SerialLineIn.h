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
// Project includes

class Updater;

/**
 * Monitors serial input, compiles a line buffer, takes actions when the line
 * is full.
 *
 * This is not a general-purpose component, it relies on the objects defined
 * for this sketch, because it controls them.  However, it could be split.
 * Create an application-specific "dispatch()" to handle anything that the
 * internal dispatch() couldn't deal with.
 *
 * Could even consider a more abstract system, where the serial line in 
 * emits a system signal to indicate that there is a line, and then everything
 * can consider the line.  Would have to add a facility for a "parameter"
 * to signals.
 */

class SerialLineIn: public IUpdate
{
private:
  char buf[32]; /**< Input buffer where we accumulate incoming text */
  char* current; /**< Position where next character will go. */
protected:
  /**
   * Dispatch the command given from serial to a specific command.
   *
   * Currently, it just DOES the command in this method.
   *
   * @retval true The command was handled
   * @retval false The command was unknown to this dispatcher, and ignored.
   */
  bool dispatch(void);
public:
  /**
   * Default constructor
   *
   * Just sets up internal state
   */
  SerialLineIn(void);

  /**
   * Begin operation
   *
   * Prepares for operation.  Adds self to the given updater.
   *
   * @param up Updater to add ourselves to
   */
  void begin(Updater& up);

  /**
   * Task update
   *
   * Call regularly to ensure correct operation.
   *
   * This is called only by the Updater and by unit tests
   */
  void update(void);
};
/****************************************************************************/

#endif // __SERIALLINEIN_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
