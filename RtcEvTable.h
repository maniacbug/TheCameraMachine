#ifndef __RTCEVTABLE_H__
#define __RTCEVTABLE_H__

// STL includes
// C includes
// Library includes
#include <RtcEvent.h> // for IRtc
// Project includes
#include <Connector.h>
#include <IUpdate.h>

/**
 * Example for how classes should be declared
 */

class RtcEvTable: public Connectable, public IUpdate
{
public:
  typedef prog_uint8_t evline[7];
private:
  uint32_t when;
  uint8_t signal_what;
  bool active;
  evline* table;
  evline* current;
  uint8_t num_lines;
  static const IRtc* rtc;
protected:
  void update(void);
  uint32_t get_when(void) const { return when; }
  bool get_active(void) const { return active; }
  bool is_valid(void) const;
public:
  RtcEvTable(Connector& _conn,evline*,uint8_t);
  void begin(void);
  uint32_t whenNext(void) const;

  static void setRtc(const IRtc*);

};

#endif // __RTCEVTABLE_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
