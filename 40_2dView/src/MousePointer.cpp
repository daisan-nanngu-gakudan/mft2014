#include "MousePointer.h"
#include "appConst.h"

//--------------------------------------------------------------
// setup
//
//

void MousePointer::setup(bool flag) {
    
    cout << "MousePointer::setup()" << endl;
    
    _speed = 1.0;
    
    _location = ofVec2f(ORIGIN_X, ORIGIN_Y);
    
    bSelfUpdate = flag;
    
}

//--------------------------------------------------------------
// update
//  - considers the mode. demo or IPC
//

void MousePointer::update() {
    
    if (bSelfUpdate) {
        _location.y++;
    } else {
       
    }
}

//--------------------------------------------------------------
// draw
// - accessor to ofxMouseController
//

void MousePointer::draw() {
    
    ofxMouseController::setPos(_location.x * 3,
                               _location.y * 3);
    
}


//--------------------------------------------------------------
// reset
//
//

void MousePointer::reset() {

    cout << "MousePointer::reset()" << endl;
    
    resetSpeed();
    resetLocation();

}

//--------------------------------------------------------------
// resetSpeed
//
//

void MousePointer::resetSpeed() {
    
    _speed = 0L;
    
}



//--------------------------------------------------------------
// resetLocation
//
//

void MousePointer::resetLocation() {
    
    _location = ofVec2f(ORIGIN_X, ORIGIN_Y);
    
}

//--------------------------------------------------------------
// pedal
//
//

void MousePointer::pedal() {
    
    if (bSelfUpdate) {
        _speed += 0.1;
    }
    
}

//--------------------------------------------------------------
// resetLocation
//
//

void MousePointer::setHandle(float norm) {
    
    if (bSelfUpdate) {
        _steer = norm;
    }
}

//--------------------------------------------------------------
// resetLocation
//
//

void MousePointer::resetDirection() {

    resetHandle();       // 下準備
    _direction = 0L;
    
}

//--------------------------------------------------------------
// resetHandle
//
//

void MousePointer::resetHandle() {
    
    setHandle(0L);
    
}

//--------------------------------------------------------------
// updateDirection
//  - ハンドル角を元に方角の更新をおこないます
//

void MousePointer::updateDirection() {
    
    if (bSelfUpdate) {
        _direction += ofMap(_steer, -1.0, 1.0, -PI/2 *0.1, PI/2 * 0.1);
        _direction = fmodf(_direction, TWO_PI);
        if (_direction < 0) _direction += TWO_PI;
    }
    
}
