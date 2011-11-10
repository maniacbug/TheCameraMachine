#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include <Updater.h>
#include <Connector.h>
#include <EmitButton.h>
#include <PinControl.h>

extern Updater up;
extern Connector conn;
extern EmitButton test_switch;
extern EmitButton record_button;
extern PinControl power_relay;
extern PinControl alt_relay;
extern PinControl power_led;
extern PinControl record_led;

#endif // __OBJECTS_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
