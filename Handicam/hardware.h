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

// Handicam board 

const int test_switch_pin = 9;
const int record_button_pin = 8;
const int power_led_pin = 7;
const int record_led_pin = 6;
const int other_led_pin = 5;
const int power_relay_pin = 4;
const int alt_relay_pin = A0;
const int lanc_rx_pin = 2;
const int lanc_tx_pin = 3;

#define BOARD_HANDICAM
#define HAVE_LANC
#define HAVE_RELAYS
#define HAVE_RECORD_BUTTON

#endif // __HARDWARE_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
