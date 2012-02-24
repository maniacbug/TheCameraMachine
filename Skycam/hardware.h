/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __HARDWARE_H__
#define __HARDWARE_H__

/**
 * @file hardware.h
 *
 * Pinouts for the hardware on which this sketch is running
 */

// Skycam board

const int test_switch_pin = 9;
const int power_led_pin = 12;
const int record_led_pin = 10;
const int other_led_pin = 8;
const int focus_pin = 7;
const int shutter_pin = 13;
const int piezo_pin = A1;

#define BOARD_SKYCAM
#define HAVE_FOCUS_SHUTTER
#define HAVE_FIRE_CAMERA

#endif // __HARDWARE_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
