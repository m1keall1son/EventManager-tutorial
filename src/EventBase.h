//
//  EventBase.h
//  ObserverPattern
//
//  Created by Mike Allison on 3/28/15.
//
//

#pragma once

using EventType = std::string;

using EventBaseRef = std::shared_ptr<class EventBase>;

class EventBase {
    
public:
    
    const double& getTimeStamp(){ return mTimeStamp; }
    
    virtual const EventType& getType() = 0;
    
    virtual ~EventBase(){}
    
protected:
    
    EventBase( const double& timeStamp ):mTimeStamp(timeStamp){}

private:
    
    double mTimeStamp;
    
};

using PrintNameEventRef = std::shared_ptr< class PrintNameEvent >;

class PrintNameEvent : public EventBase {
    
public:
    
    static PrintNameEventRef create(){ return PrintNameEventRef( new PrintNameEvent() ); }
    
    static EventType Type;
    
    const EventType& getType() override;
    
    ~PrintNameEvent(){}
    
private:
    
    PrintNameEvent():EventBase( ci::app::getElapsedSeconds() ){}

    
};

using SayThisEventRef = std::shared_ptr< class SayThisEvent >;

class SayThisEvent : public EventBase {
    
public:
    
    static SayThisEventRef create( const std::string& phrase ){ return SayThisEventRef( new SayThisEvent( phrase ) ); }
    
    static EventType Type;
    
    const EventType& getType() override;
    
    const std::string& getPhrase() { return mPhrase; }
    
    ~SayThisEvent(){}
    
private:
    
    SayThisEvent( const std::string& phrase ):EventBase( ci::app::getElapsedSeconds() ), mPhrase(phrase) {}
    std::string mPhrase;
};