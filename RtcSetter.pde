// STL includes
// C includes
// Library includes
#include <RTClib.h>

// Project includes
#include <RtcSetter.h>

/****************************************************************************/

void RtcSetter::begin(void)
{
}

/****************************************************************************/

void RtcSetter::update(void)
{
  static char buf[21];

  if ( Serial.available() && Serial.peek() == 'T'  )
  {
    Serial.read(); // Skip past the starting 'T'

    char* current = buf;
    char* end = buf + sizeof(buf) - 1;
    char c = Serial.read();
    while ( current < end && c != '\n' )
    {
      *current++ = c;
      c = Serial.read();
    }
    *current++ = 0;
    buf[11] = 0;
    rtc->adjust(DateTime(buf,buf+12).unixtime());
  }
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp
