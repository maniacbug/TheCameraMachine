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

/**
 * Monitors serial input, compiles a line buffer, takes actions when the line
 * is full.
 */

class SerialLineIn: public IUpdate
{
private:
  char buf[32];
  char* current;
protected:
  void dispatch(void);
public:
  SerialLineIn(void);
  void update(void);
};
/****************************************************************************/

#endif // __SERIALLINEIN_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp