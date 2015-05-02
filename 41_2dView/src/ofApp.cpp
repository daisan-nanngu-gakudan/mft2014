#include "ofApp.h"
#include "ofxOsc.h"
#include "ofxMouseController.h"

static const float DESKTOP_WIDTH  = 1400;
static const float DESKTOP_HEIGHT = 900;

ofxOscReceiver mReceiver;
float mX, mY;
bool bGotMess;

//--------------------------------------------------------------
void ofApp::setup(){
    mReceiver.setup(12022);
    mX = 0;
    mY = 0;
    bGotMess = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    bGotMess = false;
    while (mReceiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        mReceiver.getNextMessage(&m);
        if (m.getAddress() == "/dsng2/ctl/px")
        {
            mX = m.getArgAsFloat(0) + (DESKTOP_WIDTH * 0.5);
        }
        if (m.getAddress() == "/dsng2/ctl/py")
        {
            mY = m.getArgAsFloat(0) + (DESKTOP_HEIGHT * 0.5);
        }
        bGotMess = true;
    }
    ofSetWindowTitle(ofToString(mX, 0) + ":" + ofToString(mY, 0));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (bGotMess) ofxMouseController::setPos(mX, mY);
    
//        if (bGotMess) ofxMouseController::setPos(1000, 300  );
    
    ofDrawBitmapString(ofToString(mX) + " | " + ofToString(mY), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
