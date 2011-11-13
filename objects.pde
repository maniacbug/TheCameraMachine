#include <Connector.h>

#include <objects.h>
#include <hardware.h>
#include <signals.h>
#include <rtc.h>

Updater up;
Connector conn;
EmitButton test_switch(conn,test_switch_pin,signal_power_on,signal_power_off);
EmitButton record_button(conn,record_button_pin,signal_start_record,signal_stop_record);
PinControl power_relay(conn,power_relay_pin,signal_power_off,signal_power_on);
PinControl alt_relay(conn,alt_relay_pin,signal_alt_relay_off,signal_alt_relay_on);
PinControl power_led(conn,power_led_pin,signal_power_off,signal_power_on);
PinControl record_led(conn,record_led_pin,signal_stop_record,signal_start_record);
RtcSetter clock_setter(&Rtc);
LancControl camera(conn,lanc_command_pin,lanc_data_pin);

// vim:cin:ai:sts=2 sw=2 ft=cpp
