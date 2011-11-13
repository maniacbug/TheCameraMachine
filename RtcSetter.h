#ifndef __RTCSETTER_H__
#define __RTCSETTER_H__

// STL includes
// C includes
// Library includes
#include <RtcEvent.h> // for IRtc
#include <IUpdate.h>
// Project includes

/**
 * Monitors serial input, and sets the time 
 * 
 * Send something like "TNov 01 2011 01:02:03\n" and be sure to pad
 * with zeroes
 */

class RtcSetter: public IUpdate
{
private:
  IRtc* rtc;
protected:
public:
  RtcSetter(IRtc* _rtc): rtc(_rtc) {}
  void begin(void);
  void update(void);
};

#endif // __RTCSETTER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
