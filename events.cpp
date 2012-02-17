// Framework includes
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
// Project includes
#include "events.h"
#include "signals.h"

// Warning, this table must be in clock order, earliest events first

const uint8_t events_table[][8] PROGMEM = {
  //YY,MM,DD HH MM SS,CH, signal
  { 12, 2,16,22, 0, 0, 0,signal_power_on },
  { 12, 2,16,22, 0,10, 0,signal_start_record },
  { 12, 2,16,22, 1,10, 0,signal_stop_record },
  { 12, 2,16,22, 1,20, 0,signal_power_off  },
  
  { 12, 2,16,23, 0, 0, 0,signal_power_on },
  { 12, 2,16,23, 0,10, 0,signal_start_record },
  { 12, 2,16,23, 1,10, 0,signal_stop_record },
  { 12, 2,16,23, 1,20, 0,signal_power_off  },
 
  { 12, 2,17, 0, 0, 0, 0,signal_power_on },
  { 12, 2,17, 0, 0,10, 0,signal_start_record },
  { 12, 2,17, 0, 1,10, 0,signal_stop_record },
  { 12, 2,17, 0, 1,20, 0,signal_power_off  },

  { 12, 2,17, 1, 0, 0, 0,signal_power_on },
  { 12, 2,17, 1, 0,10, 0,signal_start_record },
  { 12, 2,17, 1, 1,10, 0,signal_stop_record },
  { 12, 2,17, 1, 1,20, 0,signal_power_off  },

  { 12, 2,17, 2, 0, 0, 0,signal_power_on },
  { 12, 2,17, 2, 0,10, 0,signal_start_record },
  { 12, 2,17, 2, 1,10, 0,signal_stop_record },
  { 12, 2,17, 2, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17, 3, 0, 0, 0,signal_power_on },
  { 12, 2,17, 3, 0,10, 0,signal_start_record },
  { 12, 2,17, 3, 1,10, 0,signal_stop_record },
  { 12, 2,17, 3, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17, 4, 0, 0, 0,signal_power_on },
  { 12, 2,17, 4, 0,10, 0,signal_start_record },
  { 12, 2,17, 4, 1,10, 0,signal_stop_record },
  { 12, 2,17, 4, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17, 5, 0, 0, 0,signal_power_on },
  { 12, 2,17, 5, 0,10, 0,signal_start_record },
  { 12, 2,17, 5, 1,10, 0,signal_stop_record },
  { 12, 2,17, 5, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17, 5,35, 0, 0,signal_power_on },
  { 12, 2,17, 5,35,10, 0,signal_start_record },
  { 12, 2,17, 5,36,10, 0,signal_stop_record },
  { 12, 2,17, 5,36,20, 0,signal_power_off  },
                         
  { 12, 2,17, 6, 0, 0, 0,signal_power_on },
  { 12, 2,17, 6, 0,10, 0,signal_start_record },
  { 12, 2,17, 6, 1,10, 0,signal_stop_record },
  { 12, 2,17, 6, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17, 7, 0, 0, 0,signal_power_on },
  { 12, 2,17, 7, 0,10, 0,signal_start_record },
  { 12, 2,17, 7, 1,10, 0,signal_stop_record },
  { 12, 2,17, 7, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17, 8, 0, 0, 0,signal_power_on },
  { 12, 2,17, 8, 0,10, 0,signal_start_record },
  { 12, 2,17, 8, 1,10, 0,signal_stop_record },
  { 12, 2,17, 8, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17, 8,30, 0, 0,signal_power_on },
  { 12, 2,17, 8,30,10, 0,signal_start_record },
  { 12, 2,17, 8,31,10, 0,signal_stop_record },
  { 12, 2,17, 8,31,20, 0,signal_power_off  },
                         
  { 12, 2,17, 9, 0, 0, 0,signal_power_on },
  { 12, 2,17, 9, 0,10, 0,signal_start_record },
  { 12, 2,17, 9, 1,10, 0,signal_stop_record },
  { 12, 2,17, 9, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17,10, 0, 0, 0,signal_power_on },
  { 12, 2,17,10, 0,10, 0,signal_start_record },
  { 12, 2,17,10, 1,10, 0,signal_stop_record },
  { 12, 2,17,10, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17,11, 0, 0, 0,signal_power_on },
  { 12, 2,17,11, 0,10, 0,signal_start_record },
  { 12, 2,17,11, 1,10, 0,signal_stop_record },
  { 12, 2,17,11, 1,20, 0,signal_power_off  },
  
  { 12, 2,17,11,30, 0, 0,signal_power_on },
  { 12, 2,17,11,30,10, 0,signal_start_record },
  { 12, 2,17,11,31,10, 0,signal_stop_record },
  { 12, 2,17,11,31,20, 0,signal_power_off  },
                         
  { 12, 2,17,12, 0, 0, 0,signal_power_on },
  { 12, 2,17,12, 0,10, 0,signal_start_record },
  { 12, 2,17,12, 1,10, 0,signal_stop_record },
  { 12, 2,17,12, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17,13, 0, 0, 0,signal_power_on },
  { 12, 2,17,13, 0,10, 0,signal_start_record },
  { 12, 2,17,13, 1,10, 0,signal_stop_record },
  { 12, 2,17,13, 1,20, 0,signal_power_off  },
  
  { 12, 2,17,14, 0, 0, 0,signal_power_on },
  { 12, 2,17,14, 0,10, 0,signal_start_record },
  { 12, 2,17,14, 1,10, 0,signal_stop_record },
  { 12, 2,17,14, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17,15, 0, 0, 0,signal_power_on },
  { 12, 2,17,15, 0,10, 0,signal_start_record },
  { 12, 2,17,15, 1,10, 0,signal_stop_record },
  { 12, 2,17,15, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17,15,30, 0, 0,signal_power_on },
  { 12, 2,17,15,30,10, 0,signal_start_record },
  { 12, 2,17,15,31,10, 0,signal_stop_record },
  { 12, 2,17,15,31,20, 0,signal_power_off  },
                         
  { 12, 2,17,16, 0, 0, 0,signal_power_on },
  { 12, 2,17,16, 0,10, 0,signal_start_record },
  { 12, 2,17,16, 1,10, 0,signal_stop_record },
  { 12, 2,17,16, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17,17, 0, 0, 0,signal_power_on },
  { 12, 2,17,17, 0,10, 0,signal_start_record },
  { 12, 2,17,17, 1,10, 0,signal_stop_record },
  { 12, 2,17,17, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17,18, 0, 0, 0,signal_power_on },
  { 12, 2,17,18, 0,10, 0,signal_start_record },
  { 12, 2,17,18, 1,10, 0,signal_stop_record },
  { 12, 2,17,18, 1,20, 0,signal_power_off  },
  
  { 12, 2,17,18,30, 0, 0,signal_power_on },
  { 12, 2,17,18,30,10, 0,signal_start_record },
  { 12, 2,17,18,31,10, 0,signal_stop_record },
  { 12, 2,17,18,31,20, 0,signal_power_off  },
                         
  { 12, 2,17,19, 0, 0, 0,signal_power_on },
  { 12, 2,17,19, 0,10, 0,signal_start_record },
  { 12, 2,17,19, 1,10, 0,signal_stop_record },
  { 12, 2,17,19, 1,20, 0,signal_power_off  },
                         
  { 12, 2,17,20, 0, 0, 0,signal_power_on },
  { 12, 2,17,20, 0,10, 0,signal_start_record },
  { 12, 2,17,20, 1,10, 0,signal_stop_record },
  { 12, 2,17,20, 1,20, 0,signal_power_off  },
  
  { 12, 2,17,21, 0, 0, 0,signal_power_on },
  { 12, 2,17,21, 0,10, 0,signal_start_record },
  { 12, 2,17,21, 1,10, 0,signal_stop_record },
  { 12, 2,17,21, 1,20, 0,signal_power_off  },
  
  { 12, 2,17,22, 0, 0, 0,signal_power_on },
  { 12, 2,17,22, 0,10, 0,signal_start_record },
  { 12, 2,17,22, 1,10, 0,signal_stop_record },
  { 12, 2,17,22, 1,20, 0,signal_power_off  },
  
  { 12, 2,17,23, 0, 0, 0,signal_power_on },
  { 12, 2,17,23, 0,10, 0,signal_start_record },
  { 12, 2,17,23, 1,10, 0,signal_stop_record },
  { 12, 2,17,23, 1,20, 0,signal_power_off  },
};
int num_events = sizeof(events_table)/8;

// vim:cin:ai:sts=2 sw=2 ft=cpp

