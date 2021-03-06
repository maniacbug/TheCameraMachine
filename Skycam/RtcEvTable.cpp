/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

// STL includes
// C includes
// Framework includes
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
// Library includes
#include <AnyRtc.h>
#include <Updater.h>
// Project includes
#include "RtcEvTable.h"
#include "objects.h" // for logger

#if 1 
void* operator new(size_t, void* __p)
{
    return __p;
}
#endif

/****************************************************************************/

uint32_t eventtime(const RtcEvTable::evline& prog_event)
{
  RtcEvTable::evline event;
  memcpy_P(&event,&prog_event,sizeof(event));
  return DateTime(event[0],event[1],event[2],event[3],event[4],event[5]).unixtime();
}

/****************************************************************************/

void RtcEvTable::begin(Updater& up)
{
  up.add(this);
  begin();
}

/****************************************************************************/

bool RtcEvTable::is_time_now(void) const
{
  return is_valid() && RTC.now() >= whenNext();
}

/****************************************************************************/

void RtcEvTable::update(void)
{
  // We actually want to fire if now is AT or after 'when'
  if ( is_time_now() ) 
  {
    channel(current_channel())->emit(current_signal());
    current++;
  }
}

/****************************************************************************/

RtcEvTable::ev_t RtcEvTable::current_channel(void) const
{
  ev_t result;
  memcpy_P(&result,*current+6,sizeof(result));
  return result;
}

/****************************************************************************/

RtcEvTable::ev_t RtcEvTable::current_signal(void) const
{
  ev_t result;
  memcpy_P(&result,*current+7,sizeof(result));
  return result;
}

/****************************************************************************/
RtcEvTable::RtcEvTable(Connector& _conn,const evline* _table,uint8_t _num_lines, 
    uint8_t _num_channels):
	table(_table), current(_table), num_lines(_num_lines), num_channels(_num_channels) 
{
  // Placement new called over an array.  Very nasty.  But C++ affords no
  // other way to call constructors on array members.
  channels = reinterpret_cast<Channel*>( malloc( num_channels * sizeof(Connectable) ) );
  int i = num_channels;
  while (i--)
    new (channels + i) Channel(_conn);
}

/****************************************************************************/
RtcEvTable::~RtcEvTable()
{
  free(channels);
}

/****************************************************************************/

void RtcEvTable::begin(void)
{
  char buf[32];

  // First, print all out for debugging
  printf_P(PSTR("REVT %u events\n\r"),num_lines);
  while ( is_valid() )
  {
    printf_P(PSTR("REVT %s on %u %S\n\r"),DateTime(whenNext()).toString(buf,sizeof(buf)),current_channel(),logger.find_symbol(current_signal()));
    current++;
  }

  // Reset to the top
  current = table;

  // seek the current pointer to the right place
  while ( is_time_now() ) 
    current++;

  if ( is_valid() )
  {
    int signal = current_signal(); 
    printf_P(PSTR("REVT next event is %s on %u %S\n\r"),DateTime(whenNext()).toString(buf,sizeof(buf)),current_channel(),logger.find_symbol(signal));
  }
  else
    printf_P(PSTR("REVT No more events remain.\n\r"));
}

/****************************************************************************/

uint32_t RtcEvTable::whenNext(void) const
{
  if ( is_valid() )
    return eventtime(*current); 
  else
    return -1; 
}

/****************************************************************************/

void RtcEvTable::invalidate(void)
{
  current = table + num_lines;
}

/****************************************************************************/

bool RtcEvTable::is_valid(void) const
{
  return (current < table + num_lines);
}

/****************************************************************************/

RtcEvTable::Channel* RtcEvTable::channel(uint8_t _channel)
{
  if ( _channel < num_channels )
    return channels + _channel;
  else
    return NULL;
}

/****************************************************************************/

void SignalEvTable::onNotify(const Connectable* ,uint8_t signal )
{
  if ( signal == signal_start )
  {
    // Started a second ago, so the first event fires immediately
    started_at = RTC.now() - 1;
    reset();
  }
}

/****************************************************************************/

SignalEvTable::SignalEvTable(Connector& _conn,uint8_t _signal_start,const evline* events,uint8_t num_lines, uint8_t num_channels): RtcEvTable(_conn,events,num_lines,num_channels), Connectable(_conn), signal_start(_signal_start)
{
  // The initialized state of a signal ev table is the INVALID state
  invalidate();
}

/****************************************************************************/

void SignalEvTable::begin(Updater& up,Connectable* _who)
{
  RtcEvTable::begin(up);
  listen(_who);
}

/****************************************************************************/

void SignalEvTable::listen(Connectable* _who)
{
  Connectable::listen(_who,signal_start);
}

/****************************************************************************/

uint32_t SignalEvTable::whenNext(void) const
{
  if ( is_valid() )
    return RtcEvTable::whenNext() + started_at; 
  else
    return -1; 
}

/****************************************************************************/
// vim:cin:ai:sts=2 sw=2 ft=cpp
