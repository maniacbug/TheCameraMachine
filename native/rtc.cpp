#include <Arduino.h>
#include <RTC_native.h>

#include <RtcEvent.h>

#include <rtc.h>

Rtc_c Rtc;

RTC_native rtc_native;

void Rtc_c::begin(void)
{
  rtc_native.begin();

  DateTime now = rtc_native.now();
  char buf[32];
  now.toString(buf,sizeof(buf));
  printf_P(PSTR("RTC  The time is now %s\n\r"),buf);

  RtcEvent::setRtc(this);
}

bool Rtc_c::is_after(uint32_t when) const
{
  uint32_t now = rtc_native.now().unixtime();
  return now > when;
}

void Rtc_c::adjust(uint32_t new_now)
{
  rtc_native.adjust(new_now);
  
  DateTime now = rtc_native.now();
  char buf[32];
  now.toString(buf,sizeof(buf));
  printf_P(PSTR("RTC  The time is now %s\n\r"),buf);
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

