#include <RTClib.h>
#include <RtcEvent.h>

#include <objects.h>
#include <signals.h>

class MyRtcEvent: public RtcEvent
{
public:
  MyRtcEvent(int y, int m, int d, int hh, int mm, int ss, uint8_t signal);
};

MyRtcEvent::MyRtcEvent(int y, int m, int d, int hh, int mm, int ss, uint8_t signal):
  RtcEvent(::conn,DateTime(y,m,d,hh,mm,ss).unixtime(),signal)
{
}

MyRtcEvent re[] = {
  MyRtcEvent(2011,11,10,6,0,0,signal_power_on)
};

void events_begin(void)
{
  MyRtcEvent *curr = re, *end = re + sizeof(re)/sizeof(re[0]);
  while ( curr < end )
  {
    curr->begin();
    up.add(curr);
    ++curr;
  }
}
// vim:cin:ai:sts=2 sw=2 ft=cpp

