#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofSetWindowTitle(ofToString(DISP_SIZE_X) +  " "
                    +  ofToString(DISP_SIZE_Y));
    
    // OSC
    setupOsc();
    
    bDebugMode = true;
    mp.setup(bDebugMode?true:false);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (!bDebugMode) {
        updateWithOsc();
    }

    mp.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    mp.draw();
    
    if (bDebugMode) {
        drawInfo();
    }
    
}



