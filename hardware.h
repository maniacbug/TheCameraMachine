#ifndef __HARDWARE_H__
#define __HARDWARE_H__

// rcfisher1 board
#if 1

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

#if 0

const int test_switch_pin = 9;
const int record_button_pin = 8;
const int power_led_pin = 7;
const int record_led_pin = 6;
const int other_led_pin = 5;
const int power_relay_pin = 4;
const int alt_relay_pin = 3;
const int lanc_command_pin = A0;
const int lanc_data_pin = A1;

#endif

#endif // __HARDWARE_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
