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
  pinSymbol(test_led_pin,"test_led");
  pinSymbol(power_led_pin,"power_led");
  pinSymbol(record_led_pin,"record_led");
  pinSymbol(power_relay_pin,"power_relay");
  pinSymbol(alt_relay_pin,"alt_relay");
  pinSymbol(lanc_pin,"lanc");
  pinSymbol(clock_set_pin,"clock_set");
#endif

  //
  // Begin objects
  //

  Rtc.begin();
  test_switch.begin();
  record_button.begin();
  power_led.begin();
  record_led.begin();
  power_relay.begin();
  alt_relay.begin();
  clock_setter.begin();

  //
  // Begin events
  //

  events_begin();

  //
  // Connect objects
  //
 
  power_led.listen(NULL);
  record_led.listen(NULL);
  power_relay.listen(NULL);
  alt_relay.listen(NULL);
  camera.listen(NULL);

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
