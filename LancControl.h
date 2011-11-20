/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __LANCCONTROL_H__
#define __LANCCONTROL_H__

// STL includes
// C includes
// Library includes
#include <Connector.h>
// Project includes

/**
 * Control a LANC-based camera.
 *
 * @warning Not fully implemented.  Currently just controls the camera by
 * toggling the command pin.
 */

class LancControl: public Connectable
{
private:
  bool is_recording;
  int command_pin;
  int data_pin;
protected:
  virtual void onNotify(const Connectable* ,uint8_t signal );
public:
  LancControl(Connector& _conn, int _command_pin, int _data_pin);
  void begin(void);
  void listen(Connectable* _who);
  bool isRecording(void) const;
};

#endif // __LANCCONTROL_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
