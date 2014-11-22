#pragma onces
#include "ofApp.h"

//--------------------------------------------------------------
// drawInfo
//
void ofApp::drawInfo(){
    ofPopStyle();
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("demo mode (No OSC)", 20, 20);
    
    ofPushStyle();
}