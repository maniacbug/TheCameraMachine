#include <Arduino.h>
#include <RTC_native.h>

#include <RtcEvent.h>

#include <rtc.h>

RTC_native rtc_native;

void BoardRtc::begin(void)
{
  rtc_native.begin();

  DateTime now = rtc_native.now();
  char buf[32];
  now.toString(buf,sizeof(buf));
  printf_P(PSTR("RTC  The time is now %s\n\r"),buf);

  RtcEvent::setRtc(this);
}

bool BoardRtc::is_after(uint32_t when) const
{
  uint32_t now = rtc_native.now().unixtime();
  return now > when;
}

void BoardRtc::adjust(uint32_t new_now)
{
  rtc_native.adjust(new_now);
  
  DateTime now = rtc_native.now();
  char buf[32];
  now.toString(buf,sizeof(buf));
  printf_P(PSTR("RTC  The time is now %s\n\r"),buf);
}

uint32_t BoardRtc::now_unixtime(void) const
{
  return rtc_native.now().unixtime();
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

