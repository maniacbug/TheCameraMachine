## topic_skycam

Wondering if I can obsolete the old skycam software and move it all over to
TCM?

Startup sequence
1. RTC triggers
1. Listen for piezo (optionally)
1. Hold focus ( signal_focus_on )
1. Wait 1s
1. Hold shoot ( signal_shoot_on )
1. Wait 20 min
1. Release shoot ( signal_shoot_off )
1. Release focus ( signal_focus_off )

Shutdown sequence
1. RTC triggers
2. Turn off piezo

* Shoot & focus pins can be a pin control
* Piezo controller can take a signal to listen, and a signal to generate when
getting the sound.  Also a piezo to stop?

PiezoTrigger piezo(signal_window_open,signal_window_close,signal_loud_noise);

const RtcEvTable::evline events_table[] PROGMEM = {
  //YY,MM,DD HH MM SS,CH, signal
  { 12, 2,19, 7, 0, 0, 0,signal_window_open },
  { 12, 2,19, 8, 0, 0, 0,signal_window_close },
};

const RtcEvTable::evline events_skycam[] PROGMEM = {
  //YY,MM,DD HH MM SS,CH, signal
  {  0, 0, 0, 0, 0, 0, 0,signal_focus_on },
  {  0, 0, 0, 0, 0, 1, 0,signal_shoot_on },
  {  0, 0, 0, 0,20, 0, 0,signal_shoot_off },
  {  0, 0, 0, 0,20, 1, 0,signal_focus_off  },
};

In some cameras, the skycam waits for the piezo, others it does not.  This is implemented
as the wait signal for the skycam event handler.  On some it will listen for
signal_window_open.  On others, it will listen for signal_loud_noise.

The piezo will always run once triggered.  Some cameras will ignore it.  Other cameras
will act on it.

But how will we have multiple configurations??  Do I put everything in a lib except the
configurable bits??

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

