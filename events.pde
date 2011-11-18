#include <RTClib.h>
#include <RtcEvent.h>

#include <events.h>
#include <objects.h>
#include <signals.h>

MyRtcEvent::MyRtcEvent(int y, int m, int d, int hh, int mm, int ss, uint8_t signal):
  RtcEvent(::conn,DateTime(y,m,d,hh,mm,ss).unixtime(),signal), w(DateTime(y,m,d,hh,mm,ss).unixtime())
{
}

void MyRtcEvent::begin()
{
  printf_P(PSTR("MyRtcEvent %p at %lu %u\n\r"),this,get_when(),get_active());
  RtcEvent::begin();
}

MyRtcEvent re[] =
{
  MyRtcEvent(2011,12,1,0,0,0,signal_other_led_on),
  MyRtcEvent(2011,12,1,0,0,2,signal_power_on),
  MyRtcEvent(2011,12,1,0,0,6,signal_start_record),
  MyRtcEvent(2011,12,1,0,0,7,signal_stop_record),
  MyRtcEvent(2011,12,1,0,0,8,signal_start_record),
  MyRtcEvent(2011,12,1,0,0,9,signal_stop_record),
  MyRtcEvent(2011,12,1,0,0,10,signal_start_record),
  MyRtcEvent(2011,12,1,0,0,11,signal_stop_record),
  MyRtcEvent(2011,12,1,0,0,12,signal_power_off),
  MyRtcEvent(2011,12,1,0,0,13,signal_other_led_off),
};
int num_re = sizeof(re)/sizeof(re[0]);

void events_begin(void)
{
  MyRtcEvent *curr = re, *end = re + num_re;
  while ( curr < end )
  {
    curr->begin();
    up.add(curr);
    ++curr;
  }
}
// vim:cin:ai:sts=2 sw=2 ft=cpp

