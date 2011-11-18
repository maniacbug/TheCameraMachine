#ifndef __EVENTS_H__
#define __EVENTS_H__

#include <RtcEvent.h>

class MyRtcEvent: public RtcEvent
{
  uint32_t w;
public:
  MyRtcEvent(int y, int m, int d, int hh, int mm, int ss, uint8_t signal);
  void begin(void);
  uint32_t getWhen(void) const
  {
    return w;
  }
};

extern void events_begin(void);
extern MyRtcEvent re [];
extern int num_re;

#endif // __EVENTS_H__

// vim:cin:ai:sts=2 sw=2 ft=cpp

