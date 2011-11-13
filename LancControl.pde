// STL includes
// C includes
// Library includes
// Project includes
#include <signals.h>
#include <LancControl.h>

/****************************************************************************/

LancControl::LancControl(Connector& _conn, int _command_pin, int _data_pin): 
  Connectable(_conn), is_recording(false), command_pin(_command_pin),
  data_pin(_data_pin)
{
}

/****************************************************************************/

void LancControl::begin(void)
{
  pinMode(command_pin,INPUT);
  pinMode(data_pin,OUTPUT);
}

/****************************************************************************/

void LancControl::listen(Connectable* _who) 
{
  Connectable::listen(_who,signal_start_record);
  Connectable::listen(_who,signal_stop_record);
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
    printf_P(PSTR("LANC Recording\n\r"));
    break;
  case signal_stop_record:
    is_recording = false;
    printf_P(PSTR("LANC Stopping\n\r"));
    break;
  }
}

/****************************************************************************/
// vim:cin:ai:sts=2 sw=2 ft=cpp
