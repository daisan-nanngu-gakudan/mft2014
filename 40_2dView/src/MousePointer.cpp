#include "MousePointer.h"
#include "appConst.h"

//--------------------------------------------------------------
// setup
//
//

void MousePointer::setup(bool flag) {
    
    cout << "MousePointer::setup()" << endl;
    
    _speed = 1.0L;
    _location = ofVec2f(ORIGIN_X, ORIGIN_Y);
    _steer = 0L;
    _direction = 0L;
    
    bSelfUpdate = flag;
    
}

//--------------------------------------------------------------
// update
//  - considers the mode. demo or IPC
//

void MousePointer::update() {
    
    if (bSelfUpdate) {
        
        // update direction
        updateDirection();
        
        // update position
        _location.x += _speed * cos(_direction);
        _location.y += _speed * sin(_direction);

        // TODO : crop
        // Util::crop(&_location, _cropBegin, _cropEnd);
        
    } else {
       
    }
}

//--------------------------------------------------------------
// draw
// - accessor to ofxMouseController
//

void MousePointer::draw() {
    
    ofxMouseController::setPos(_location.x,
                               _location.y);
    
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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//         B i k e - m o d e l - l i k e    A  P  I
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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
// stop
//
//

void MousePointer::stop() {
    
    _speed = 0L;
    
}

//--------------------------------------------------------------
// handle
//
//

void MousePointer::handle(float norm) {
    
    if (bSelfUpdate) {
        
        _steer += norm;
        
        // clipping
        _steer = ofClamp(_steer, -1.0, 1.0);
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

        cout << "MousePointer::updateDirection()" << endl;
        
        _direction += ofMap(_steer, -1.0, 1.0, -PI/2 *0.1, PI/2 * 0.1);
        _direction = fmodf(_direction, TWO_PI);
        if (_direction < 0) _direction += TWO_PI;
    }
    
}
