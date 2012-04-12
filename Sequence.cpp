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
// Project headers
// This component's header
#include <Sequence.h>

/****************************************************************************/

Sequence::Sequence(Connector& conn,const Entry* _entries,uint8_t _signal_launch): Connectable(conn), Tictocs::Timer(0), entries(_entries), current(_entries), signal_launch(_signal_launch)
{
  disable();
  resetInterval();
}

/****************************************************************************/

void Sequence::onFired(void)
{
  disable();
  if ( isValid() ) 
  {
    emit( current->signal );
    ++current;
    resetInterval();
  }
}

/****************************************************************************/

bool Sequence::isValid(void) const
{
  return current && current->signal;
}

/****************************************************************************/

void Sequence::resetInterval(void)
{
  if ( isValid() ) 
    setInterval(current->delayms);
}

/****************************************************************************/
void Sequence::begin(Updater& updater,Connectable* whom)
{
  Tictocs::Timer::begin(updater);
  listen(whom,signal_launch);
}
/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp
