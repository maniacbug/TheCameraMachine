#ifndef __RTC_H__
#define __RTC_H__

#include <RtcEvent.h>
#include <RTClib.h>

class BoardRtc: public IRtc
{
  uint32_t now;
public:
  void begin(void);
  bool is_after(uint32_t when) const; // { return now > when; }
  void adjust(uint32_t new_now);
};

#endif // __RTC_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
