#include <Wire.h>
#include <RTClib.h>
#include <RTC_DS1307.h>
#include <rtc.h>

static RTC_DS1307 RTC;

void BoardRtc::begin(void)
{
  Wire.begin();
  RTC.begin();
  
  char buf[32];
  RTC.now().toString(buf,sizeof(buf));
  printf_P(PSTR("RTC  The time is now %s\n\r"),buf);
}

bool BoardRtc::is_after(uint32_t when) const
{
  return now_unixtime() > when;
}

void BoardRtc::adjust(uint32_t new_now)
{
  RTC.adjust(new_now);

  char buf[32];
  RTC.now().toString(buf,sizeof(buf));
  printf_P(PSTR("RTC  The time is now %s\n\r"),buf);
}

uint32_t BoardRtc::now_unixtime(void) const
{
  DateTime result = RTC.now();
  return result.unixtime();
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

