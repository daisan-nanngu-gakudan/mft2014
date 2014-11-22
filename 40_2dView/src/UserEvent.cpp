#pragma once
#include "ofApp.h"

//--------------------------------------------------------------
//
void ofApp::keyPressed(int key){
    
    switch (key) {
        case OF_KEY_UP:
            mp.pedal();
            break;
        case OF_KEY_DOWN:
            break;
        case OF_KEY_LEFT:
            break;
        case OF_KEY_RIGHT:
            break;
        case ' ':
            bDebugMode = !bDebugMode;
            mp.bSelfUpdate = bDebugMode;
            break;
        case 'a':
            break;
        case '1':
            mp.reset();
            break;
        default:
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
