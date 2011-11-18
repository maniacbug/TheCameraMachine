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
    Serial.print((char)Serial.read()); // Skip past the starting 'T'

    char* current = buf;
    char* end = buf + sizeof(buf) - 1;
    int c = -1;
    while ( c == -1 )
      c = Serial.read();
    while ( current < end && c != '\n' )
    {
      Serial.print((char)c);
      *current++ = c;

      c = -1;
      while ( c == -1 )
	c = Serial.read();
    }
    *current++ = 0;
    buf[11] = 0;
    rtc->adjust(DateTime(buf,buf+12).unixtime());
  }
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp
