// Framework includes
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
#include <Wire.h>
// Library includes
#include <AnyRtc.h>
#include <RTC_DS1307.h>
// Project includes
#include "rtc.h"

static RTC_DS1307 rtc_internal;

extern void print_time(void);

void rtc_begin(void)
{
  Wire.begin();
  RTC.begin(&rtc_internal);
  print_time();
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

