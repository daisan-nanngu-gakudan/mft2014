#include "ofMain.h"
#include "ofApp.h"
#include "appConst.h"

//========================================================================
int main( ){
    
	ofSetupOpenGL(winSize[0], winSize[1], OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
