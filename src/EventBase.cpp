//
//  EventBase.cpp
//  ObserverPattern
//
//  Created by Mike Allison on 3/28/15.
//
//

#include "EventBase.h"

EventType PrintNameEvent::Type = "Print Name Event";
const EventType& PrintNameEvent::getType() { return Type; }

EventType SayThisEvent::Type = "Say This Event";
const EventType& SayThisEvent::getType() { return Type; }
