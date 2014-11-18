#pragma once
#include <iostream>
#include "ofMain.h"
#include "appConst.h"

class Bike {
private:
	
public:
	float _speed;
	float _steer;
	float _direction;   //  as radian
	ofVec2f _location;  // is this here or other Class?
	// ofVec2f _fieldSize; // is this here or other Class?
    list<ofVec2f> _locHist;
    
    ofVec2f _cropBegin;
    ofVec2f _cropEnd;
    
    Bike();
	
	void setup();
    void setupCropSettings(const ofVec2f begin, const ofVec2f end); // crop の設定
	
    void update();
	void updateDirection();
	void draw();        // for self drawing on oF App
    void drawTrack();   // for self drawing on oF App
	void report();      // report position in stdout
	
	void pedal();
	void stop();
	void handle(float normed);
    
    // debug
    void setLocation(ofVec2f loc);
    void setHandle(float st);
    void resetHandle();
};

namespace Util{
    void crop(ofVec2f* src, ofVec2f corner1, ofVec2f corner2);
}