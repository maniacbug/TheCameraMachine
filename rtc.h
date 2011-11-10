#ifndef __RTC_H__
#define __RTC_H__

#include <RtcEvent.h>

class Rtc: public IRtc
{
  uint32_t now;
public:
  bool is_after(uint32_t when) const { return now > when; }
};

#endif // __RTC_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
