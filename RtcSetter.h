#ifndef __RTCSETTER_H__
#define __RTCSETTER_H__

// STL includes
// C includes
// Library includes
#include <RtcEvent.h> // for IRtc
// Project includes

/**
 * Monitors serial input, and sets the time 
 */

class RtcSetter
{
private:
  IRtc* rtc;
  int pin;
protected:
public:
  RtcSetter(IRtc* _rtc, int _pin): rtc(_rtc), pin(_pin) {}
  void update(void);
};

#endif // __RTCSETTER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
