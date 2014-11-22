#pragma once
#include "ofxMouseController.h"
#include <iostream>

class MousePointer {
    
public:
    
    float _speed;
    ofVec2f _location;
    
    float _steer;       // as normed float -1.0 .. 1.0
	float _direction;   // as radian 0 .. 2PI
    
        // OSC受信時は OFF
        // 座標を外部から受け取って使用する場合はOFF
    bool bSelfUpdate; // self update mode
    
    void setup(bool selfUpdate);
    void update();
    void draw(); // access to ofxMouseController(CGEvent wrapper)
    
    void reset();
    void resetSpeed();
    void resetLocation();
    

    
    // bike model-like api
    void pedal();
    void stop();
    void handle(float norm);    // update steer with diff
    
    void setHandle(float norm);
    void resetDirection();
    void resetHandle();
    
private:
	void updateDirection();
};
