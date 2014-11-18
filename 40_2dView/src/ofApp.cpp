#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofSetWindowTitle(ofToString(DISP_SIZE_X) +  " " +  ofToString(DISP_SIZE_Y));
    
    setupOsc();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    updateOsc();
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
}


//--------------------------------------------------------------
//
void ofApp::keyPressed(int key){
	fprintf(stdout, "key pressed [%d]\n", key);
    switch (key) {
        case OF_KEY_UP:
            
            break;
        case OF_KEY_DOWN:
            
            break;
        case OF_KEY_LEFT:
            
            break;
        case OF_KEY_RIGHT:
            
            break;
        case ' ':
            
            break;
        case 'a':
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


