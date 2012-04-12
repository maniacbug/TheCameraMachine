/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

// Library includes
#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <MemoryFree.h>
#include <AnyRtc.h>
#include <Tictocs.h>
//Project includes
#include "RtcEvTable.h"
#include "signals.h"
#include "events.h"
#include "Sequence.h"

//
// MAIN EVENT TABLE for skycam 
//

const RtcEvTable::evline events_table[] PROGMEM = {
  //YY,MM,DD HH MM SS,CH, signal
  { 12, 4,26,15, 0, 0, 0,signal_shutter_tap },
  { 12, 4,26,15,15, 0, 0,signal_shutter_tap },
  { 12, 4,26,16, 0, 0, 0,signal_shutter_tap },
  { 12, 4,26,16,15, 0, 0,signal_shutter_tap },
  { 12, 4,26,17, 0, 0, 0,signal_shutter_tap },
  { 12, 4,26,17,15, 0, 0,signal_shutter_tap },
  { 12, 4,26,18, 0, 0, 0,signal_shutter_tap },
  { 12, 4,26,18,15, 0, 0,signal_shutter_tap },
  
};
int num_events = sizeof(events_table)/sizeof(RtcEvTable::evline);

//
// SEQUENCE shutter_tap 
//

const Sequence::Entry seq_shutter_tap_entries[] PROGMEM = {
  // wait ms, then do this
  { 0	    , signal_focus_on },
  { 1000    , signal_shutter_on },
  { 500	    , signal_shutter_off },
  { 0	    , signal_focus_off },
  { 0, 0 }, // always terminate with a {0,0}
};

// vim:cin:ai:sts=2 sw=2 ft=cpp
