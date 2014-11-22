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
        Util::crop(&_location, _cropBegin, _cropEnd);
        
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
// setupCropSettings
//
//

void MousePointer::setupCropSettings(ofVec2f corner1, ofVec2f corner2){
    _cropBegin.x = corner1.x;
    _cropBegin.y = corner1.y;
    _cropEnd.x   = corner2.x;
    _cropEnd.y   = corner2.y;
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
        
        _direction += ofMap(_steer, -1.0, 1.0, -PI/2 *0.1, PI/2 * 0.1);
        _direction = fmodf(_direction, TWO_PI);
        if (_direction < 0) _direction += TWO_PI;
    }
    
}

//--------------------------------------------------------------
// crop()
// 座標sを、端点p1, 端点p2から作られる領域でクロッピングします。
// 参照渡しによる、座標の更新を行います
//
void Util::crop(ofVec2f *s, const ofVec2f p1, const ofVec2f p2){
    if (s->x > p2.x) {s->x = p1.x; cout << "croped! 1" << endl;}
    if (s->x < p1.x) {s->x = p2.x; cout << "croped! 2" << endl;}
    if (s->y > p2.y) {s->y = p1.y; cout << "croped! 3" << endl;}
    if (s->y < p1.y) {s->y = p2.y; cout << "croped! 4" << endl;}
};
