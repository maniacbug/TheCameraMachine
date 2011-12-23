#include <events.h>
#include <signals.h>

// Warning, this table must be in clock order, earliest events first

prog_uint8_t events_table[][8] PROGMEM = {
  //YY,MM,DD HH MM SS,CH, signal
  { 11,11,19, 0, 0, 0, 0,signal_power_on },
  { 11,11,19, 0, 0,10, 0,signal_start_record },
  { 11,11,19, 0, 0,12, 0,signal_stop_record },
  { 11,11,19, 0, 0,14, 0,signal_power_off  },
                         
  { 11,11,19, 1, 0, 0, 0,signal_power_on },
  { 11,11,19, 1, 0,10, 0,signal_start_record },
  { 11,11,19, 1, 0,12, 0,signal_stop_record },
  { 11,11,19, 1, 0,14, 0,signal_power_off  },
                         
  { 11,11,19, 1,30, 0, 0,signal_power_on },
  { 11,11,19, 1,30,10, 0,signal_start_record },
  { 11,11,19, 1,30,12, 0,signal_stop_record },
  { 11,11,19, 1,30,14, 0,signal_power_off  },
                         
  { 11,11,19, 2, 0, 0, 0,signal_power_on },
  { 11,11,19, 2, 0,10, 0,signal_start_record },
  { 11,11,19, 2, 0,12, 0,signal_stop_record },
  { 11,11,19, 2, 0,14, 0,signal_power_off  },
                         
  { 11,11,19, 3, 0, 0, 0,signal_power_on },
  { 11,11,19, 3, 0,10, 0,signal_start_record },
  { 11,11,19, 3, 0,12, 0,signal_stop_record },
  { 11,11,19, 3, 0,14, 0,signal_power_off  },
                         
  { 11,11,19, 4, 0, 0, 0,signal_power_on },
  { 11,11,19, 4, 0,10, 0,signal_start_record },
  { 11,11,19, 4, 0,12, 0,signal_stop_record },
  { 11,11,19, 4, 0,14, 0,signal_power_off  },
  
  { 11,11,19, 4,30, 0, 0,signal_power_on },
  { 11,11,19, 4,30,10, 0,signal_start_record },
  { 11,11,19, 4,30,12, 0,signal_stop_record },
  { 11,11,19, 4,30,14, 0,signal_power_off  },
                         
  { 11,11,19, 5, 0, 0, 0,signal_power_on },
  { 11,11,19, 5, 0,10, 0,signal_start_record },
  { 11,11,19, 5, 0,12, 0,signal_stop_record },
  { 11,11,19, 5, 0,14, 0,signal_power_off  },
                         
  { 11,11,19, 6, 0, 0, 0,signal_power_on },
  { 11,11,19, 6, 0,10, 0,signal_start_record },
  { 11,11,19, 6, 0,12, 0,signal_stop_record },
  { 11,11,19, 6, 0,14, 0,signal_power_off  },
  
};
int num_events = sizeof(events_table)/8;

// vim:cin:ai:sts=2 sw=2 ft=cpp

