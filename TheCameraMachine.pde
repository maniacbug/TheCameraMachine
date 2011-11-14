#include <hardware.h>
#include <objects.h>
#include <rtc.h>
#include <signals.h>
#include <events.h>

void setup(void)
{
  //
  // Announce
  //

  Serial.begin(57600);
  Serial.println("TheCameraMachine - maniacbug@ymail.com");

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
  pinSymbol(lanc_command_pin,"lanc_command");
  pinSymbol(lanc_data_pin,"lanc_data");
#endif

  //
  // Begin objects
  //

  Rtc.begin();
  test_switch.begin();
  record_button.begin();
  power_led.begin();
  record_led.begin();
  other_led.begin();
  power_relay.begin();
  alt_relay.begin();
  clock_setter.begin();
  camera.begin();

  //
  // Begin events
  //

  events_begin();

  //
  // Connect objects
  //

  power_led.listen(NULL);
  record_led.listen(NULL);
  other_led.listen(NULL);
  power_relay.listen(NULL);
  alt_relay.listen(NULL);
  camera.listen(NULL);
  conn.setLogger(&logger);

  //
  // Logger symbols
  //

  logger.setSymbol(signal_power_on, "power_on");
  logger.setSymbol(signal_power_off, "power_off");
  logger.setSymbol(signal_start_record, "start_record");
  logger.setSymbol(signal_stop_record, "stop_record");
  logger.setSymbol(signal_alt_relay_on, "alt_relay_on");
  logger.setSymbol(signal_alt_relay_off, "alt_relay_off");
  logger.setSymbol(signal_other_led_on, "other_led_on");
  logger.setSymbol(signal_other_led_off, "other_led_off");

  logger.setSymbol(&test_switch, "test_switch");
  logger.setSymbol(&record_button, "record_button");
  logger.setSymbol(&power_relay, "power_relay");
  logger.setSymbol(&alt_relay, "alt_relay");
  logger.setSymbol(&power_led, "power_led");
  logger.setSymbol(&record_led, "record_led");
  logger.setSymbol(&other_led, "other_led");
  logger.setSymbol(&camera, "camera");

  //
  // Timeline
  //

  //
  // Register updating objects
  //

  up.add(&test_switch);
  up.add(&record_button);
  up.add(&clock_setter);
}

void loop(void)
{
  up.update();
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
