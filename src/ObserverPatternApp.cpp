#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "EventManager.h"
#include "TestThings.h"

using namespace ci;
using namespace ci::app;
using namespace std;

///Event Manager is a singleton, can be extended for indivual situations, like event managers within event managers
///Events base can be extended to pass any data and can be dynamically cast on the receiving end

class ObserverPatternApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void keyUp( KeyEvent event )override;
	void update() override;
	void draw() override;
    
    ///its very important to note that your registered things wont copy their event manager registration when copy constructed, using shared pointers makes it more explicit
    
    std::vector<BaseThingRef> mThings;
    
};

void ObserverPatternApp::setup()
{
    
    mThings.push_back( Printer::create( "mike" ) );
    mThings.push_back( Printer::create( "steve" ) );
    mThings.push_back( Printer::create( "joe" ) );

    mThings.push_back( Sayer::create() );
    mThings.push_back( Sayer::create() );

}

void ObserverPatternApp::keyUp(cinder::app::KeyEvent event)
{
    if(event.getChar() == ' ')mThings.clear();
    
}

void ObserverPatternApp::mouseDown( MouseEvent event )
{
    ///send some events
    EventManager::get()->queueEvent( PrintNameEvent::create() );
    EventManager::get()->triggerEvent( SayThisEvent::create("i'm instantly triggered") );
    EventManager::get()->queueEvent( SayThisEvent::create("i'm here!") );

}

void ObserverPatternApp::update()
{
    ///just update the manager to empty the queue
    EventManager::get()->update();
}

void ObserverPatternApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( ObserverPatternApp, RendererGl )
