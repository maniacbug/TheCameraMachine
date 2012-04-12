/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

// Framework includes
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

// Library includes
#include <Connector.h>

// Project includes
#include "objects.h"
#include "hardware.h"
#include "signals.h"
#include "rtc.h"
#include "events.h"
#include "Sequence.h"

// Common objects
Updater up;
Connector conn;
EmitButton test_switch(conn,test_switch_pin,signal_start_record,signal_stop_record);
PinControl power_led(conn,power_led_pin,signal_power_off,signal_power_on);
PinControl record_led(conn,record_led_pin,signal_stop_record,signal_start_record);
PinControl other_led(conn,other_led_pin,signal_other_led_off,signal_other_led_on);
EepromLogger logger;
RtcEvTable events(conn,events_table,num_events);
SerialLineIn tty;

// Specialized objects for SKYCAM
PinControl focus(conn,focus_pin,signal_focus_off,signal_focus_on);
PinControl shutter(conn,shutter_pin,signal_shutter_off,signal_shutter_on);
PinControl power_relay(conn,power_relay_pin,signal_power_relay_off,signal_power_relay_on);
PinControl alt_relay(conn,alt_relay_pin,signal_alt_relay_off,signal_alt_relay_on);
Sequence seq_shutter_tap(conn,seq_shutter_tap_entries,signal_shutter_tap);
// vim:cin:ai:sts=2 sw=2 ft=cpp
