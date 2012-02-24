/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __EVENTS_H__
#define __EVENTS_H__

// Project includes
#include "RtcEvTable.h"

/**
 * @file events.h
 *
 * Declaration of application-specific events table
 */

extern const RtcEvTable::evline events_table[];
extern int num_events;
extern const RtcEvTable::evline events_fire_camera[];
extern int num_events_fire_camera;
extern const RtcEvTable::evline events_skycam_gh2[];
extern int num_events_skycam_gh2;
#endif // __EVENTS_H__

// vim:cin:ai:sts=2 sw=2 ft=cpp

