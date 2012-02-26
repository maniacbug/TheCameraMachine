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

//
// MAIN EVENT TABLE for skycam 
//

const RtcEvTable::evline events_table[] PROGMEM = {
  //YY,MM,DD HH MM SS,CH, signal
  { 12, 2,26,15, 0, 0, 0,signal_start_record },
  { 12, 2,26,15,15, 0, 0,signal_stop_record },
  { 12, 2,26,16, 0, 0, 0,signal_start_record },
  { 12, 2,26,16,15, 0, 0,signal_stop_record },
  { 12, 2,26,17, 0, 0, 0,signal_start_record },
  { 12, 2,26,17,15, 0, 0,signal_stop_record },
  { 12, 2,26,18, 0, 0, 0,signal_start_record },
  { 12, 2,26,18,15, 0, 0,signal_stop_record },
  
};
int num_events = sizeof(events_table)/sizeof(RtcEvTable::evline);

//
// FIRE CAMERA EVENTS for signal_start_record OR
// signal_stop_record (skycam GH-2)
//

const RtcEvTable::evline events_fire_camera[] PROGMEM = {
  //YY,MM,DD HH MM SS,CH, signal
  {  0, 0, 0, 0, 0, 0, 0,signal_focus_on },
  {  0, 0, 0, 0, 0, 3, 0,signal_shutter_tap },
  {  0, 0, 0, 0, 0, 4, 0,signal_focus_off },
};
int num_events_fire_camera = sizeof(events_fire_camera)/sizeof(RtcEvTable::evline);

// vim:cin:ai:sts=2 sw=2 ft=cpp
