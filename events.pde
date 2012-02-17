#include <events.h>
#include <signals.h>

// Warning, this table must be in clock order, earliest events first

const uint8_t events_table[][8] PROGMEM = {
  //YY,MM,DD HH MM SS,CH, signal
  { 12, 2,16, 7, 0, 0, 0,signal_power_on },
  { 12, 2,16, 7, 0,10, 0,signal_start_record },
  { 12, 2,16, 7, 1,10, 0,signal_stop_record },
  { 12, 2,16, 7, 1,20, 0,signal_power_off  },
                         
  { 12, 2,16, 8, 0, 0, 0,signal_power_on },
  { 12, 2,16, 8, 0,10, 0,signal_start_record },
  { 12, 2,16, 8, 1,10, 0,signal_stop_record },
  { 12, 2,16, 8, 1,20, 0,signal_power_off  },
                         
  { 12, 2,16, 8,30, 0, 0,signal_power_on },
  { 12, 2,16, 8,30,10, 0,signal_start_record },
  { 12, 2,16, 8,31,10, 0,signal_stop_record },
  { 12, 2,16, 8,31,20, 0,signal_power_off  },
                         
  { 12, 2,16, 9, 0, 0, 0,signal_power_on },
  { 12, 2,16, 9, 0,10, 0,signal_start_record },
  { 12, 2,16, 9, 1,10, 0,signal_stop_record },
  { 12, 2,16, 9, 1,20, 0,signal_power_off  },
                         
  { 12, 2,16,10, 0, 0, 0,signal_power_on },
  { 12, 2,16,10, 0,10, 0,signal_start_record },
  { 12, 2,16,10, 1,10, 0,signal_stop_record },
  { 12, 2,16,10, 1,20, 0,signal_power_off  },
                         
  { 12, 2,16,11, 0, 0, 0,signal_power_on },
  { 12, 2,16,11, 0,10, 0,signal_start_record },
  { 12, 2,16,11, 1,10, 0,signal_stop_record },
  { 12, 2,16,11, 1,20, 0,signal_power_off  },
  
  { 12, 2,16,11,30, 0, 0,signal_power_on },
  { 12, 2,16,11,30,10, 0,signal_start_record },
  { 12, 2,16,11,31,10, 0,signal_stop_record },
  { 12, 2,16,11,31,20, 0,signal_power_off  },
                         
  { 12, 2,16,12, 0, 0, 0,signal_power_on },
  { 12, 2,16,12, 0,10, 0,signal_start_record },
  { 12, 2,16,12, 1,10, 0,signal_stop_record },
  { 12, 2,16,12, 1,20, 0,signal_power_off  },
                         
  { 12, 2,16,13, 0, 0, 0,signal_power_on },
  { 12, 2,16,13, 0,10, 0,signal_start_record },
  { 12, 2,16,13, 1,10, 0,signal_stop_record },
  { 12, 2,16,13, 1,20, 0,signal_power_off  },
  
  { 12, 2,16,14, 0, 0, 0,signal_power_on },
  { 12, 2,16,14, 0,10, 0,signal_start_record },
  { 12, 2,16,14, 1,10, 0,signal_stop_record },
  { 12, 2,16,14, 1,20, 0,signal_power_off  },
                         
  { 12, 2,16,15, 0, 0, 0,signal_power_on },
  { 12, 2,16,15, 0,10, 0,signal_start_record },
  { 12, 2,16,15, 1,10, 0,signal_stop_record },
  { 12, 2,16,15, 1,20, 0,signal_power_off  },
                         
  { 12, 2,16,15,30, 0, 0,signal_power_on },
  { 12, 2,16,15,30,10, 0,signal_start_record },
  { 12, 2,16,15,31,10, 0,signal_stop_record },
  { 12, 2,16,15,31,20, 0,signal_power_off  },
                         
  { 12, 2,16,16, 0, 0, 0,signal_power_on },
  { 12, 2,16,16, 0,10, 0,signal_start_record },
  { 12, 2,16,16, 1,10, 0,signal_stop_record },
  { 12, 2,16,16, 1,20, 0,signal_power_off  },
                         
  { 12, 2,16,17, 0, 0, 0,signal_power_on },
  { 12, 2,16,17, 0,10, 0,signal_start_record },
  { 12, 2,16,17, 1,10, 0,signal_stop_record },
  { 12, 2,16,17, 1,20, 0,signal_power_off  },
                         
  { 12, 2,16,18, 0, 0, 0,signal_power_on },
  { 12, 2,16,18, 0,10, 0,signal_start_record },
  { 12, 2,16,18, 1,10, 0,signal_stop_record },
  { 12, 2,16,18, 1,20, 0,signal_power_off  },
  
  { 12, 2,16,18,30, 0, 0,signal_power_on },
  { 12, 2,16,18,30,10, 0,signal_start_record },
  { 12, 2,16,18,31,10, 0,signal_stop_record },
  { 12, 2,16,18,31,20, 0,signal_power_off  },
                         
  { 12, 2,16,19, 0, 0, 0,signal_power_on },
  { 12, 2,16,19, 0,10, 0,signal_start_record },
  { 12, 2,16,19, 1,10, 0,signal_stop_record },
  { 12, 2,16,19, 1,20, 0,signal_power_off  },
                         
  { 12, 2,16,20, 0, 0, 0,signal_power_on },
  { 12, 2,16,20, 0,10, 0,signal_start_record },
  { 12, 2,16,20, 1,10, 0,signal_stop_record },
  { 12, 2,16,20, 1,20, 0,signal_power_off  },
  
};
int num_events = sizeof(events_table)/8;

// vim:cin:ai:sts=2 sw=2 ft=cpp

