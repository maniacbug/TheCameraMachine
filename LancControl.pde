// STL includes
// C includes
// Library includes
// Project includes
#include <signals.h>
#include <LancControl.h>

/****************************************************************************/

LancControl::LancControl(Connector& _conn): Connectable(_conn), is_recording(false) 
{
}

/****************************************************************************/

void LancControl::listen(Connectable* _who) 
{
  Connectable::listen(_who,signal_start_record);
}

/****************************************************************************/

bool LancControl::isRecording(void) const 
{ 
  return is_recording; 
}

/****************************************************************************/

void LancControl::onNotify(const Connectable* ,uint8_t signal )
{
  switch (signal)
  {
  case signal_start_record:
    is_recording = true;
    break;
  }
}

/****************************************************************************/
// vim:cin:ai:sts=2 sw=2 ft=cpp
