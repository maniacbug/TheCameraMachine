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

Updater up;
Connector conn;
EmitButton test_switch(conn,test_switch_pin,signal_power_on,signal_power_off);
EmitButton record_button(conn,record_button_pin,signal_toggle_record);
PinControl power_relay(conn,power_relay_pin,signal_power_off,signal_power_on);
PinControl alt_relay(conn,alt_relay_pin,signal_alt_relay_off,signal_alt_relay_on);
PinControl power_led(conn,power_led_pin,signal_power_off,signal_power_on);
PinControl record_led(conn,record_led_pin,signal_stop_record,signal_start_record);
PinControl other_led(conn,other_led_pin,signal_other_led_off,signal_other_led_on);
LancControl camera(conn,lanc_rx_pin,lanc_tx_pin);
EepromLogger logger;
RtcEvTable events(conn,events_table,num_events);
SignalEvTable fire_camera(conn,signal_fire_camera,events_fire_camera,num_events_fire_camera);
SerialLineIn tty;
// vim:cin:ai:sts=2 sw=2 ft=cpp
