#include <hardware.h>
#include <objects.h>
#include <rtc.h>
#include <signals.h>

RtcEvent re1(conn,DateTime(2011,11,10,5,59,0).unixtime(),signal_power_on);

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

  re1.begin();

  //
  // Connect objects
  //
 
  power_led.listen(NULL);
  record_led.listen(&record_button);
  power_relay.listen(&test_switch);
  alt_relay.listen(NULL);

  //
  // Timeline
  //

  //
  // Register updating objects
  //

  up.add(&test_switch);
  up.add(&record_button);
  up.add(&re1);
}

void loop(void)
{
  up.update();
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
