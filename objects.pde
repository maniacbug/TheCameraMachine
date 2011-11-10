#include <Connector.h>

#include <objects.h>
#include <hardware.h>
#include <signals.h>

Updater up;
Connector conn;
EmitButton test_switch(conn,test_switch_pin,signal_power_on,signal_power_off);
PinControl power_led(conn,power_led_pin,signal_power_off,signal_power_on);
PinControl record_led(conn,record_led_pin,signal_stop_record,signal_start_record);
// vim:cin:ai:sts=2 sw=2 ft=cpp
