#ifndef __RTC_H__
#define __RTC_H__

#include <RtcEvent.h>
#include <RTClib.h>

class Rtc_c: public IRtc
{
  uint32_t now;
public:
  void begin(void);
  bool is_after(uint32_t when) const; // { return now > when; }
};

extern Rtc_c Rtc;

#endif // __RTC_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
