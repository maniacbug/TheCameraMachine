#ifndef __LANCCONTROL_H__
#define __LANCCONTROL_H__

// STL includes
// C includes
// Library includes
#include <Connector.h>
// Project includes

/**
 * Example for how classes should be declared
 */

class LancControl: public Connectable
{
private:
  bool is_recording;
protected:
 virtual void onNotify(const Connectable* ,uint8_t signal );
public:
  LancControl(Connector& _conn);
  void listen(Connectable* _who);
  bool isRecording(void) const;
};

#endif // __LANCCONTROL_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
