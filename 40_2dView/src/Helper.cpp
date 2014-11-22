#pragma onces
#include "ofApp.h"

//--------------------------------------------------------------
// drawInfo
//
void ofApp::drawInfo(){
    
    ofPopStyle();
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("demo mode (No OSC)", 20, 20);
    
    stringstream s1;
    s1  << "- - mouse info - -" << endl
        << "speed     :  " << ofToString(mp._speed,2) << endl
        << "steer     : "  << (mp._steer < 0 ?'-':' ')
                           << ofToString(abs(mp._steer),2) << endl
        << "direction :  " << ofToString(mp._direction, 2) << endl
        << "location  :  " << ofToString(mp._location.x, 0) << ", "
                           << ofToString(mp._location.y, 0) << endl;
    
    ofDrawBitmapString(s1.str(), 20, 40);
    
    ofPushStyle();
}