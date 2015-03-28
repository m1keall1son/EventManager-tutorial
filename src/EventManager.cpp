//
//  EventManager.cpp
//  ObserverPattern
//
//  Created by Mike Allison on 3/28/15.
//
//

#include "EventManager.h"

///essentially a singleton event manager

static EventManagerRef sManager = nullptr;

EventManagerRef EventManager::get()
{
    
    if(!sManager){
        sManager = EventManagerRef( new EventManager() );
    }
    return sManager;
}

EventRegistration EventManager::registerListener( const EventType &type, const EventListener& listener )
{
    EventRegistration reg;
    for( auto& handler : mHandlers ){
        
        if( handler.first == type ){
            reg = handler.second->connect(listener);
            return reg;
        }
        
    }
    
    mHandlers.push_back(std::make_pair(type, EventHandlerRef( new ci::signals::Signal<void( EventBaseRef )>() ) ));
    reg = mHandlers.back().second->connect( listener );
    return reg;
}

void EventManager::queueEvent( EventBaseRef event )
{
    mQueue.push_back(event);
}
void EventManager::triggerEvent( EventBaseRef event )
{
    for( auto & handler : mHandlers ){
        if( handler.first == event->getType() ){
            handler.second->emit( event );
        }
    }
}

void EventManager::update()
{
    if(!mHandlers.empty()){
        ///check for empty signals
        auto it = mHandlers.begin();
        while( it != mHandlers.end() ){
            
            auto connections = it->second->getNumSlots();
            
            if( connections == 0 ){
                it = mHandlers.erase(it);
            }else{
                it++;
            }
        }
    }
    
    if(!mQueue.empty()){
        ///empty the queue each frame
        for(  int i = 0; i < mQueue.size(); i++ ){
            
            auto & front = mQueue.front();
            
            for( auto & handler : mHandlers ){
                if( handler.first == front->getType() ){
                    handler.second->emit(front);
                    break;
                }
            }
            
            mQueue.pop_front();
        }
    }
}