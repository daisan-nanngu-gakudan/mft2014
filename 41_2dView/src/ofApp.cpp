#include "ofApp.h"
#include "ofxOsc.h"
#include "ofxMouseController.h"

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
            mX = m.getArgAsFloat(0);
        }
        if (m.getAddress() == "/dsng2/ctl/py")
        {
            mY = m.getArgAsFloat(0);
        }
        bGotMess = true;
    }

    if (bGotMess) ofxMouseController::setPos(mX, mY);
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofDrawBitmapString(ofToString(mX) + " | " + ofToString(mY), 20, 20);
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
