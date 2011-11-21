# The Camera Machine

Pre-programmable camera controller.

# Pre-requisites

## Arduino Libraries (Required)

1. Tictocs library
2. AnyRtc
3. MemoryFree

## Native Components (Optional)

Only needed if you want to target the native machine and run tests.

1. cxxtest
2. Arduino Native Core

# Configuring

## Events List

The primary configuration for the controller is to modify the list of events
which control what happens when.  To do so, edit events.pde, and modify the
'events\_table' array.

Here is an example.  It says that at Midnight (00:00:00) on Nov 19, 2011, the
"signal\_power\_on" should be raised.  This will cause any components who are
listening for that signal to do their thing.

Be warned that the table must be in chronological order, with the earliest
events coming first.

    prog_uint8_t events_table[][7] PROGMEM = {
      //YY,MM,DD HH MM SS, signal
      { 11,11,19, 0, 0, 0, signal_power_on },
      { 11,11,19, 0, 0,10, signal_start_record },
      { 11,11,19, 0, 0,12, signal_stop_record },
      { 11,11,19, 0, 0,14, signal_power_off  },
    };

A full list of signals is available in the file signals.h.

## Hardware

The hardware configuration is described in the file hardware.h.  If the board
is laid out differently, modify this file.

# Running

## How to send commands

While the unit is running, certain useful information will be printed to the
Serial Monitor.  Likewise, certain comments are accepted to work with the
unit.  To send a command, connect the serial monitor, select "Line Endings:
CR+LF", type a command into the line entry box, and hit "Send".  Commands can
be sent at any time.

## EEPROM Log

While the sketch is running, a log of all activity is captured to the EEPROM.
This allows a node to run in a remote location, and then later recover a log
of what happened for troubleshooting.

To spew the contents of the log, send the command 'E'. 

## Real-time clock (RTC)

The sketch expects a RTC connected.  To set the clock, use the following 
commands:

* Dyymmdd: Set the current DATE, e.g. "D110102" to set the date to Jan 2, 2011.
* Thhmmss: Set the current TIME, e.g. "T140530" to set the time to 2:05:30pm.

There are also certain test situations supported.

* @0: Set the clock to a very early date (Jan 01, 2000)
* @1: Set the clock to the first event in the event table.  This will cause the first event to fire immediately.
* @N: Set the clock to the next upcoming event in the event table.  This will cause it to fire immediately.

Thus a good way to test the system is to send '@1', verify that it worked, and then '@N' over and over again, testing the outcome of each event.

## Free memory

To check on how the memory is doing, send the command 'F'.

# Architecture

This sketch implements the asychronous object model provided by the Tictocs 
library.  Everything which can happen in the system is managed by an
independent object.

Objects which monitor some external state implement the IUpdate interface and 
add themselves to the Updater, which causes them to use a little slide of
loop() time to monitor their state.

These objects are:

* events: Monitors the clock, raises signals each time the clock passes an entry in the events\_table.
* tty: Monitors the serial line in to listen for commands the user enters.
* test\_switch: Monitors the test switch on the board
* record\_botton: Monitors the record button on the board

When something interesting happens, objects 'emit' one of the signals in 
signals.h.  Receiving objects who are interested in those 'listen' for the
signal, and get 'notified' when an object emits one.  The entire logic of
the sketch is implemented in the signal-based relationship between objects
and in each object's onNotify handler.

The objects.h file declares these objects, and the objects.pde file
defines them, and all the wiring up of the objects is handled in the
setup() function.

Where possible, I've pushed the logic into the Tictocs library, making
re-usable general purpose objects.

Some object classes are unavoidably application-specific.  Anything which
includes the objects.h header relies on application-specific objects.
In the future it may be useful to refactor the general pieces out.