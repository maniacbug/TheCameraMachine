// STL includes
// C includes
// Library includes
#include <RTClib.h>

// Project includes
#include <objects.h>
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
    while ( current < end && c != '\n' && c != '\r' )
    {
      Serial.print((char)c);
      *current++ = c;

      c = -1;
      while ( c == -1 )
	c = Serial.read();
    }
    *current++ = 0;
    Serial.println();

    // Special hard-code hacks
    uint32_t new_time = 0; 
    if ( !strcmp(buf,"1") )
    {
      //new_time = DateTime(2011,12,1,0,0,0).unixtime();
      new_time = events.whenNext();
    }
    else if ( !strcmp(buf,"0") )
    {
      new_time = DateTime(2011,1,1,0,0,0).unixtime();
    }
    else
    {
      buf[11] = 0;
      new_time = DateTime(buf,buf+12).unixtime();
    }


    rtc->adjust(new_time);
    printf_P(PSTR("RTST RtcSetter is now %lu\n\r"),new_time);
  }
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp
