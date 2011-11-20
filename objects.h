#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include <Updater.h>
#include <Connector.h>
#include <EmitButton.h>
#include <PinControl.h>
#include <EepromLogger.h>
#include <LancControl.h>
#include <RtcEvTable.h>
#include <SerialLineIn.h> 
#include <rtc.h>

extern Updater up;
extern Connector conn;
extern BoardRtc Rtc;
extern EmitButton test_switch;
extern EmitButton record_button;
extern PinControl power_relay;
extern PinControl alt_relay;
extern PinControl power_led;
extern PinControl record_led;
extern PinControl other_led;
extern LancControl camera;
extern EepromLogger logger;
extern RtcEvTable events;
extern SerialLineIn tty;

#endif // __OBJECTS_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
