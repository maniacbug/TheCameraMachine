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
#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <MemoryFree.h>
#include <AnyRtc.h>
#include <Tictocs.h>
// Project includes
#include "hardware.h"
#include "objects.h"
#include "rtc.h"
#include "signals.h"
#include "events.h"
#include "printf.h"

const int marker = 0; // Unused

#ifdef VERSION_H
#include <version.h>
#else
const char program_version[] = "Unknown";
#endif

void setup(void)
{
  //
  // Announce
  //

  Serial.begin(57600);
  printf_begin();
  printf_P(PSTR("\n\rTheCameraMachine - maniacbug@ymail.com\n\r"));
  printf_P(PSTR("VER. %s\n\r"),program_version);
  printf_P(PSTR("FREE %u\n\r"),freeMemory());
  
  //
  // Pin Symbols
  //

#if NATIVE
  pinSymbol(test_switch_pin,"test_switch");
  pinSymbol(record_button_pin,"record_button");
  pinSymbol(other_led_pin,"other_led");
  pinSymbol(power_led_pin,"power_led");
  pinSymbol(record_led_pin,"record_led");
  pinSymbol(power_relay_pin,"power_relay");
  pinSymbol(alt_relay_pin,"alt_relay");
  pinSymbol(lanc_rx_pin,"lanc_rx");
  pinSymbol(focus_pin,"focus");
  pinSymbol(shutter_pin,"shutter");
  pinSymbol(piezo_pin,"piezo");
#endif

  //
  // Begin objects
  //

  rtc_begin();
  test_switch.begin();
  power_led.begin();
  record_led.begin();
  other_led.begin();
  focus.begin();
  shutter_tap.begin();

#ifdef HAVE_RELAYS
  power_relay.begin();
  alt_relay.begin();
#endif

#ifdef HAVE_RECORD_BUTTON
  record_button.begin();
#endif

#ifdef HAVE_LANC
  camera.begin();
#endif

#ifdef HAVE_FIRE_CAMERA 
  fire_camera.begin();
#endif

  //
  // Connect objects
  //

  // Note that these listen to any emitters.  To restrict only to
  // a single channel, they would have to be pointed at that channel.
  power_led.listen(NULL);
  other_led.listen(NULL);
  shutter_tap.listen(NULL);
  focus.listen(NULL);
  
#ifdef HAVE_RELAYS
  power_relay.listen(NULL);
  alt_relay.listen(NULL);
#endif
  
#ifdef HAVE_RECORD_BUTTON
  record_led.listen(NULL);
#endif
  
#ifdef HAVE_LANC
  camera.listen(NULL);
#endif
  
#ifdef HAVE_FIRE_CAMERA 
  fire_camera.listen(NULL);
#endif

  conn.setLogger(&logger);

  //
  // Logger symbols
  //

  logger.setSymbol(signal_power_on, PSTR("power_on"));
  logger.setSymbol(signal_power_off, PSTR("power_off"));
  logger.setSymbol(signal_start_record, PSTR("start_record"));
  logger.setSymbol(signal_stop_record, PSTR("stop_record"));
  logger.setSymbol(signal_alt_relay_on, PSTR("alt_relay_on"));
  logger.setSymbol(signal_alt_relay_off, PSTR("alt_relay_off"));
  logger.setSymbol(signal_other_led_on, PSTR("other_led_on"));
  logger.setSymbol(signal_other_led_off, PSTR("other_led_off"));
  logger.setSymbol(signal_toggle_record, PSTR("toggle_record"));
  logger.setSymbol(signal_fire_camera, PSTR("fire_camera"));
  logger.setSymbol(signal_focus_on, PSTR("focus_on"));
  logger.setSymbol(signal_focus_off, PSTR("focus_off"));
  logger.setSymbol(signal_shutter_tap, PSTR("shutter_tap"));

  logger.setSymbol(&test_switch, PSTR("test_switch"));
  logger.setSymbol(&power_led, PSTR("power_led"));
  logger.setSymbol(&record_led, PSTR("record_led"));
  logger.setSymbol(&other_led, PSTR("other_led"));
  logger.setSymbol(&focus, PSTR("focus"));
  logger.setSymbol(&shutter_tap, PSTR("shutter_tap"));
  logger.setSymbol(events.channel(0), PSTR("events ch#0"));
  
#ifdef HAVE_RELAYS
  logger.setSymbol(&power_relay, PSTR("power_relay"));
  logger.setSymbol(&alt_relay, PSTR("alt_relay"));
#endif

#ifdef HAVE_RECORD_BUTTON
  logger.setSymbol(&record_button, PSTR("record_button"));
#endif
  
#ifdef HAVE_LANC
  logger.setSymbol(&camera, PSTR("camera"));
#endif
  
#ifdef HAVE_FIRE_CAMERA 
  logger.setSymbol(&fire_camera, PSTR("fire_camera"));
  logger.setSymbol(fire_camera.channel(0), PSTR("fire_camera ch#0"));
#endif
  
  // Begin the logger after all the symbols are set.
  logger.begin();
  events.begin();

  //
  // Register updating objects
  //

  up.add(&test_switch);
  up.add(&events);
  up.add(&shutter_tap);
  up.add(&tty);
  
#ifdef HAVE_RECORD_BUTTON
  up.add(&record_button);
#endif

#ifdef HAVE_FIRE_CAMERA 
  up.add(&fire_camera);
#endif
}

void loop(void)
{
  up.update();
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
