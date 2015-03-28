//
//  EventManager.h
//  ObserverPattern
//
//  Created by Mike Allison on 3/28/15.
//
//

#pragma once
#include "EventBase.h"

using EventManagerRef = std::shared_ptr<class EventManager>;

using EventListener = std::function<void( EventBaseRef )>;

using EventRegistration = ci::signals::Connection;

using EventHandler = ci::signals::Signal<void( EventBaseRef )>;

using EventHandlerRef = std::shared_ptr< EventHandler >;

using EventHandlerRefByType = std::pair< EventType, EventHandlerRef >;

///Event Manager interface
class EventManagerBase {
    
public:
    
    ///register listening delegates. delagates can remove themselves with the returned registration object.
    virtual EventRegistration registerListener(  const EventType &type, const EventListener& listener ) = 0;
    
    ///queue events in order to be executed at update
    virtual void queueEvent( EventBaseRef event ) = 0;
    
    ///instantly trigger event
    virtual void triggerEvent( EventBaseRef event ) = 0;
    
    ///run through our event queue and dispatch events
    virtual void update() = 0;
    
};


class EventManager : public EventManagerBase {
    
public:
    
    static EventManagerRef get();
    
    ///delagates can remove themselves with the returned registration
    virtual EventRegistration registerListener(  const EventType &type, const EventListener& listener ) override;
    
    ///queue events in order to be executed at update
    virtual void queueEvent( EventBaseRef event )override;
    
    ///instantly trigger event
    virtual void triggerEvent( EventBaseRef event )override;
    
    virtual void update()override;
    
protected:
    
    std::vector< EventHandlerRefByType > mHandlers;
    std::deque< EventBaseRef > mQueue;
    
};