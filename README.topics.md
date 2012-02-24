## topic_subdirs

To make mulitple configurations easier, I am copying files into individual directories.

## topic_skycam

### Skycam GH-2

The skycam GH-2 is now supported, using the #define SKYCAM_GH2.

The behaviour is:

1. Await the signal_fire_camera
2. Hold the focus for 1s
3. Tap the shutter for 0.5s
4. Release shutter and focus

This is encoded in events_skycam_gh2.

Note that there is a little fuzz in step #4.  The focus is actually released 1s
after it`s held down, just because timing is based on an absolute clock, not
relative to the previous step.

### Piezo

The old skycam needed the piezo, so that will be the next thing to come in.

* Piezo controller can take a signal to listen, and a signal to generate when
getting the sound.  Also a piezo to stop?

PiezoTrigger piezo(signal_window_open,signal_window_close,signal_loud_noise);

In some cameras, the skycam waits for the piezo, others it does not.  This is implemented
as the wait signal for the skycam event handler.  On some it will listen for
signal_window_open.  On others, it will listen for signal_loud_noise.

The piezo will always run once triggered.  Some cameras will ignore it.  Other cameras
will act on it.

### Configuration

The basic idea is to leave the objects which control focus and shutter around all the
time just to reduce complexity.  Only the SignalEvTable needs to be redefined based
on which camera is in use.

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

