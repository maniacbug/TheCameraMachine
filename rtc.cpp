#include<rtc.h>

Rtc_c Rtc;

void Rtc_c::begin(void)
{
}

bool Rtc_c::is_after(uint32_t when) const
{
  return now > when;
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

