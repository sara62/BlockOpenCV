#include "cinder/app/AppBasic.h"
#include "cinder/Capture.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include "CinderOpenCv.h"
#include "cinder/Vector.h"
#include "cinder/params/Params.h"


using namespace ci;
using namespace ci::app;
using namespace std;

// size of our window and such
#define SCREEN_WIDTH 1020 
#define SCREEN_HEIGHT 704

class SimpleCameraApp : public AppBasic {
public:
    // setup our functions/methods
    void prepareSettings(Settings *settings);
	void setup();
	void update();
	void draw();
    void keyDown(KeyEvent event);
    
    // declare our variables
    Capture			imgCapture;
    gl::Texture		imgTexture;
    
    
    cv::VideoCapture capture;



    
};
void SimpleCameraApp::prepareSettings( Settings *settings ) {
	settings->setWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    settings->setFrameRate(60);
}

void SimpleCameraApp::setup()
{
    // Create our camera
    capture = cv::VideoCapture(0);
    
    if(capture.isOpened()){
        cout << "this might work.." << endl;
        
    }else{
        cout << "shyt.. maybe some other day." << endl;
    }
    
    gl::enableAlphaBlending();
    
    
}

void SimpleCameraApp::keyDown( KeyEvent event )
{
    switch( event.getCode() )
	{
        case KeyEvent::KEY_ESCAPE:
            quit();
            break;
        default:
            break;
	}
}

void SimpleCameraApp::update()
{
    if(capture.grab()){
        cv::Mat newFrame;
        capture >> newFrame;
        
        imgTexture = gl::Texture(fromOcv( newFrame ));
        
    }
}

void SimpleCameraApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	
	if( imgTexture ) {
		gl::draw( imgTexture, getWindowBounds());
        
	}
    else{
        gl::drawString("Loading image please wait..",getWindowCenter());

    }    
    
}

CINDER_APP_BASIC( SimpleCameraApp, RendererGl )
