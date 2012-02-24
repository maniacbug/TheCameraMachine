/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include <Updater.h>
#include <Connector.h>
#include <EmitButton.h>
#include <PinControl.h>
// Project includes
#include "RtcEvTable.h"
#include "SerialLineIn.h" 
#include "EepromLogger.h"
#include "LancControl.h"
#include "PinTimer.h"

/**
 * @file objects.h
 *
 * All application-specific objects.  Any file which includes this header is by
 * definition an applciation-specific component.
 */

extern Updater up;
extern Connector conn;
extern EmitButton test_switch;
extern EmitButton record_button;
extern PinControl power_relay;
extern PinControl alt_relay;
extern PinControl power_led;
extern PinControl record_led;
extern PinControl other_led;
extern PinControl focus;
extern PinTimer shutter_tap;
extern EepromLogger logger;
extern RtcEvTable events;
extern SignalEvTable fire_camera;
extern SerialLineIn tty;

#ifdef HAVE_LANC
extern LancControl camera;
#endif

#endif // __OBJECTS_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp
