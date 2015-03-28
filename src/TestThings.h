//
//  TestThings.h
//  ObserverPattern
//
//  Created by Mike Allison on 3/28/15.
//
//

#pragma once
#include "EventManager.h"

///In order to work with the event manager, any obect must register in its constructor, save the registration, and disconnect when appropriate, most likely on destruction

using BaseThingRef = std::shared_ptr<class BaseThing >;

class BaseThing {};

using PrinterRef = std::shared_ptr< class Printer >;

class Printer : public BaseThing {
    
public:
    
    static PrinterRef create( const std::string& name ){ return PrinterRef( new Printer( name ) );  }
    
    ///this function will handle an event, note the function signiture is void( EventBaseRef )
    void print( EventBaseRef ){
        ci::app::console() << mName << std::endl;
    }
    
    ~Printer(){
        ///disconnect the event when the object goes out of scope
        mHandlerRegistration.disconnect();
    }
    
private:
    
    Printer( const std::string& name ):mName(name){
        
        ///register the event handling function with a specific type of event, could register for many events
        mHandlerRegistration = EventManager::get()->registerListener(PrintNameEvent::Type, std::bind( &Printer::print, this, std::placeholders::_1 ) );
        
    }
    
    ///keep track of the registration so it can be disconnected at somepoint.
    EventRegistration mHandlerRegistration;
    std::string mName;
};

using SayerRef = std::shared_ptr<class Sayer>;

class Sayer : public BaseThing {
    
public:
    
    static SayerRef create(){ return SayerRef( new Sayer ); }
    
    void say( EventBaseRef event ){
        
        ///This event contains data that this handler needs to carry out its function, cast the event to the same type the handler was registered with
        ///now the event with be of type SayThisEventRef and we can use the appropriate getters, like getPhrase
        auto cast_event = std::dynamic_pointer_cast<SayThisEvent>(event);
        
        ci::app::console() << "sayer says: " << cast_event->getPhrase() << std::endl;
    }
    
    
    ~Sayer(){
        mHandlerRegistration.disconnect();
    }
    
private:
    
    Sayer(){
        
        mHandlerRegistration = EventManager::get()->registerListener( SayThisEvent::Type, std::bind(&Sayer::say, this, std::placeholders::_1) );
        
    }
    
    EventRegistration mHandlerRegistration;
};

