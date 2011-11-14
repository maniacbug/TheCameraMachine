#include <rtc.h>

void BoardRtc::begin(void)
{
}

bool BoardRtc::is_after(uint32_t when) const
{
  return now > when;
}

void BoardRtc::adjust(uint32_t new_now)
{
  now = new_now;
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

