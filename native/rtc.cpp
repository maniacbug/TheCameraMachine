#include <RTC_native.h>

static RTC_native rtc_internal;

extern void print_time(void);

void rtc_begin(void)
{
  RTC.begin(&rtc_internal);
  print_time();
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

