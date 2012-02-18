// Framework includes
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
// Project includes
#include "events.h"
#include "signals.h"

// Warning, these tables must be in clock order, earliest events first

//
// MAIN EVENT TABLE
//

const RtcEvTable::evline events_table[] PROGMEM = {
  //YY,MM,DD HH MM SS,CH, signal
  { 12, 2,19,13, 0, 0, 0,signal_fire_camera },
  { 12, 2,19,14, 0, 0, 0,signal_fire_camera },
  { 12, 2,19,15, 0, 0, 0,signal_fire_camera },
  { 12, 2,19,16, 0, 0, 0,signal_fire_camera },
  { 12, 2,19,17, 0, 0, 0,signal_fire_camera },
  { 12, 2,19,18, 0, 0, 0,signal_fire_camera },
  { 12, 2,19,19, 0, 0, 0,signal_fire_camera },
  { 12, 2,19,20, 0, 0, 0,signal_fire_camera },
  
};
int num_events = sizeof(events_table)/sizeof(RtcEvTable::evline);

//
// EVENT TABLE for signal_fire_camera
//

const RtcEvTable::evline events_fire_camera[] PROGMEM = {
  //YY,MM,DD HH MM SS,CH, signal
  {  0, 0, 0, 0, 0, 0, 0,signal_power_on },
  {  0, 0, 0, 0, 0,10, 0,signal_start_record },
  {  0, 0, 0, 0, 1,10, 0,signal_stop_record },
  {  0, 0, 0, 0, 1,20, 0,signal_power_off  },
};
int num_events_fire_camera = sizeof(events_fire_camera)/sizeof(RtcEvTable::evline);

// vim:cin:ai:sts=2 sw=2 ft=cpp

