#include <RTClib.h>
#include <RtcEvent.h>

#include <events.h>
#include <objects.h>
#include <signals.h>

// Warning, this table must be in clock order, earliest events first

prog_uint8_t events_table[][7] PROGMEM = {
  //YY,MM,DD HH MM SS, signal
  { 11,12, 1, 0, 0, 0, signal_power_on },
  { 11,12, 1, 0, 0, 2, signal_start_record },
  { 11,12, 1, 0, 0, 6, signal_stop_record },
  { 11,12, 1, 0, 0, 7, signal_power_off  },
};
int num_events = sizeof(events)/7;

// vim:cin:ai:sts=2 sw=2 ft=cpp

