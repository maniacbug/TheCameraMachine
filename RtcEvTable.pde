// STL includes
// C includes
// Library includes
#include <RTClib.h>
// Project includes
#include <RtcEvTable.h>

const IRtc* RtcEvTable::rtc = NULL;

/****************************************************************************/

uint32_t eventtime(RtcEvTable::evline& event)
{
  return DateTime(event[0],event[1],event[2],event[3],event[4],event[5]).unixtime();
}
/****************************************************************************/

void RtcEvTable::update(void)
{
  // We actually want to fire if now is AT or after 'when', so check whether
  // it's AFTER a second BEFORE we're supposed to fire.
  if ( rtc && current < table + num_lines && rtc->is_after(whenNext()-1) )
  {
    emit((*current)[6]);
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
  // seek the current pointer to the right place
  if ( rtc )
  {
    while ( current <= table + num_lines && rtc->is_after(whenNext()) )
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
  return eventtime(*current); 
}

/****************************************************************************/
// vim:cin:ai:sts=2 sw=2 ft=cpp
