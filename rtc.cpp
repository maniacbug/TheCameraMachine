#include <rtc.h>

Rtc_c Rtc;

void Rtc_c::begin(void)
{
}

bool Rtc_c::is_after(uint32_t when) const
{
  return now > when;
}

void Rtc_c::adjust(uint32_t new_now)
{
  now = new_now;
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

