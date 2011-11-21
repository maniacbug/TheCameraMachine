#include <Wire.h>
#include <AnyRtc.h>
#include <RTC_DS1307.h>
#include <rtc.h>

static RTC_DS1307 rtc_internal;

extern void print_time(void);

void rtc_begin(void)
{
  Wire.begin();
  RTC.begin(&rtc_internal);
  print_time();
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

