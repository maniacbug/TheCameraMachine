#include <hardware.h>
#include <objects.h>
#include <rtc.h>
#include <signals.h>
#include <events.h>
#include <MemoryFree.h>
#include <printf.h>

void setup(void)
{
  //
  // Announce
  //

  Serial.begin(57600);
  Serial.println("TheCameraMachine - maniacbug@ymail.com");
  Serial.println(freeMemory());
  printf_begin();
  
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
  logger.setRtc(&Rtc);

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

  logger.setSymbol(&test_switch, PSTR("test_switch"));
  logger.setSymbol(&record_button, PSTR("record_button"));
  logger.setSymbol(&power_relay, PSTR("power_relay"));
  logger.setSymbol(&alt_relay, PSTR("alt_relay"));
  logger.setSymbol(&power_led, PSTR("power_led"));
  logger.setSymbol(&record_led, PSTR("record_led"));
  logger.setSymbol(&other_led, PSTR("other_led"));
  logger.setSymbol(&camera, PSTR("camera"));
  
  // Begin the logger after all the symbols are set.
  logger.begin();

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
