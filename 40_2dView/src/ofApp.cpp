#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofSetWindowTitle(ofToString(DISP_SIZE_X) +  " "
                    +  ofToString(DISP_SIZE_Y));
    
    ofBackground(30, 30, 130);
    
    // OSC
    setupOsc();
    
    bDebugMode = true;
    
    mp.setup(bDebugMode?true:false);
    mp.setupCropSettings(DESKTOPCORNER_BEGIN, DESKTOPCORNER_END);
    
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



