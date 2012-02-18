## topic_rtce_split

Created SignalEvTable as a specialization of RtcEvTable.  This allows us to
have a repeatable sequence of events which is triggered by a signal.

Allows us to do this:

const RtcEvTable::evline events_table[] PROGMEM = {
  //YY,MM,DD HH MM SS,CH, signal
  { 12, 2,19, 7, 0, 0, 0,signal_fire_camera },
  { 12, 2,19, 7,30, 0, 0,signal_fire_camera },
  { 12, 2,19, 8, 0, 0, 0,signal_fire_camera },
  { 12, 2,19, 8,30, 0, 0,signal_fire_camera },
  
};
const RtcEvTable::evline events_fire_camera[] PROGMEM = {
  //YY,MM,DD HH MM SS,CH, signal
  {  0, 0, 0, 0, 0, 0, 0,signal_power_on },
  {  0, 0, 0, 0, 0,10, 0,signal_start_record },
  {  0, 0, 0, 0, 1,10, 0,signal_stop_record },
  {  0, 0, 0, 0, 1,20, 0,signal_power_off  },
};

