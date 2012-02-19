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

// rcfisher1 board (sky camera)
#if 0

const int test_switch_pin = 9;
const int record_button_pin = A2;
const int power_led_pin = 12;
const int record_led_pin = 10;
const int other_led_pin = 8;
const int power_relay_pin = 7;
const int alt_relay_pin = 3;
const int lanc_command_pin = 13;
const int lanc_data_pin = A1;

#endif

// video board
#if 1

const int test_switch_pin = 9;
const int record_button_pin = 8;
const int power_led_pin = 7;
const int record_led_pin = 6;
const int other_led_pin = 5;
const int power_relay_pin = 4;
const int alt_relay_pin = A0;
const int lanc_rx_pin = 2;
const int lanc_tx_pin = 3;
const int focus_pin = A1;
const int shutter_pin = A2;
const int piezo_pin = A3;

// Define only one of these, undef the rest

#define SKYCAM_GH2
#undef HANDYCAM

#endif

#endif // __HARDWARE_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
