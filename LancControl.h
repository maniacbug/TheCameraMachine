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
#include <SoftwareSerial.h>
// Project includes

/**
 * Control a LANC-based camera.
 *
 * @warning Not fully implemented.  Currently just controls the camera by
 * pulsing the command pin.
 *
 * Currently this is application-specific only because it relies on the
 * application's signals.  Should refactor it so that the specific signals
 * used are passed in.  Then it would be truly generic and can/should be
 * abstracted into its own library.
 */

class LancControl: public Connectable
{
private:
  bool is_recording;
  SoftwareSerial lanc_serial;
protected:
  virtual void onNotify(const Connectable* ,uint8_t signal );
public:
  LancControl(Connector& _conn, int _rx_pin, int _tx_pin);
  void begin(void);
  void listen(Connectable* _who);
  bool isRecording(void) const;
};

#endif // __LANCCONTROL_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
