#pragma onces
#include "ofApp.h"

//--------------------------------------------------------------
// drawInfo
//
void ofApp::drawInfo(){
    
    ofPopStyle();
    
    stringstream s1;
    
    if (bDebugMode) {
        
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("demo mode (No OSC)", 20, 20);
        
        s1  << "- - mouse info - -" << endl
            << "speed     :  " << ofToString(mp._speed,2) << endl
            << "steer     : "  << (mp._steer < 0 ?'-':' ')
                               << ofToString(abs(mp._steer),2) << endl
            << "direction :  " << ofToString(mp._direction, 2) << endl
            << "location  :  " << ofToString(mp._location.x, 0) << ", "
                               << ofToString(mp._location.y, 0) << endl;
        
        
    } else {
        
        // use OSC
        
        ofSetColor(255, 255, 0);
        ofDrawBitmapString("OSC Mode", 20, 20);
        
        s1  << "- - message info - -" << endl
            << "DUMMY" << endl
        << "speed     :  " << ofToString(mp._speed,2) << endl
        << "steer     : "  << (mp._steer < 0 ?'-':' ')
                           << ofToString(abs(mp._steer),2) << endl
        << "direction :  " << ofToString(mp._direction, 2) << endl
        << "location  :  " << ofToString(mp._location.x, 0) << ", "
                           << ofToString(mp._location.y, 0) << endl;
        
    }
    
    ofDrawBitmapString(s1.str(), 20, 40);
    ofPushStyle();
}