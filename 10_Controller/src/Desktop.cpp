#include "Desktop.h"

//--------------------------------------------------------------
//
//
void Desktop::setup(const ofVec2f size) {
    _size = size;
    
    // 描画開始座標の設定
    _p.x = -1 * _size.x/2;
    _p.y = -1 * _size.y/2;
    
    desctopImage.loadImage("desktop.png");
}

//--------------------------------------------------------------
// update
//[design] No any update.
//
void Desktop::update() {
    
}

//--------------------------------------------------------------
// draw
// 
//
void Desktop::draw() {
    ofPushStyle();
    ofSetColor(255);
    desctopImage.draw(0, 0, _size.x, _size.y);
    
    ofFill();
    
    ofNoFill();
    ofSetColor(0, 188, 0);
    ofSetRectMode(OF_RECTMODE_CORNER);
//    ofRect(_p.x, _p.y, _size.x, _size.y);
    ofRect(0, 0, _size.x, _size.y);
    
    ofPopStyle();
}

//--------------------------------------------------------------
// getCornerBegin
//
//
ofVec2f Desktop::getCornerBegin(){
    
    cout << "getCornerBegin" << endl;
    cout << _p.x  << endl;
    cout << _p.y  << endl;

    return ofVec2f(_p.x, _p.y);
}

//--------------------------------------------------------------
// getCornerEnd
//
//
ofVec2f Desktop::getCornerEnd(){
    
    cout << "getCornerEnd" << endl;
    cout << _p.x + _size.x << endl;
    cout << _p.y + _size.y << endl;
    
    return ofVec2f(_p.x + _size.x, _p.y + _size.y);
}


