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
            mp.stop();
            break;
        case OF_KEY_LEFT:
            mp.handle(-0.1);
            break;
        case OF_KEY_RIGHT:
            mp.handle(+0.1);
            break;
        case ' ':
            bDebugMode = !bDebugMode;
            mp.bSelfUpdate = bDebugMode;
            break;
        case 'a':
            mp.reset();
            break;
        case '0':
            mp.resetHandle();
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
