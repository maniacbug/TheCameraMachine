// STL includes
// C includes
// Library includes
#include <RTClib.h>
// Project includes
#include <RtcEvTable.h>
#include <objects.h>

const IRtc* RtcEvTable::rtc = NULL;

/****************************************************************************/

uint32_t eventtime(RtcEvTable::evline& prog_event)
{
  RtcEvTable::evline event;
  memcpy_P(&event,&prog_event,sizeof(event));
  return DateTime(event[0],event[1],event[2],event[3],event[4],event[5]).unixtime();
}
/****************************************************************************/

void RtcEvTable::update(void)
{
  // We actually want to fire if now is AT or after 'when', so check whether
  // it's AFTER a second BEFORE we're supposed to fire.
  if ( rtc && is_valid() && rtc->is_after(whenNext()-1) )
  {
    emit(pgm_read_byte(&((*current)[6])));
    current++;
  }
}

/****************************************************************************/
RtcEvTable::RtcEvTable(Connector& _conn,evline* _table,uint8_t _num_lines):
	Connectable(_conn), table(_table), current(_table), num_lines(_num_lines) 
{
}

/****************************************************************************/

void RtcEvTable::begin(void)
{
  char buf[32];

  // First, print all out for debugging
  if ( rtc )
  {
    printf_P(PSTR("REVT %u events\n\r"),num_lines);
    while ( is_valid() )
    {
      int signal = pgm_read_byte(&((*current)[6]));
      printf_P(PSTR("REVT %s %S\n\r"),DateTime(whenNext()).toString(buf,sizeof(buf)),logger.find_symbol(signal));
      current++;
    }
  }
  else
    printf_P(PSTR("REVT No RTC set!\n\r"));

  // Reset to the top
  current = table;

  // seek the current pointer to the right place
  if ( rtc )
  {
    while ( is_valid() && rtc->is_after(whenNext()) )
      current++;
  }
}

/****************************************************************************/

void RtcEvTable::setRtc(const IRtc* _rtc)
{
  rtc = _rtc;
}

/****************************************************************************/

uint32_t RtcEvTable::whenNext(void) const
{
  if ( is_valid() )
    return eventtime(*current); 
  else
    return eventtime(*(table + num_lines - 1)) + 1;
}

/****************************************************************************/

bool RtcEvTable::is_valid(void) const
{
  return (current < table + num_lines);
}

/****************************************************************************/
// vim:cin:ai:sts=2 sw=2 ft=cpp
