#pragma once

#include "ofMain.h"
#include "ofxStateMachine.h"
#include "ofxOculusDK2.h"
#include "ofxPostGlitch.h"
#include "ofxFPSCamera.h"
#include "ofxOsc.h"
#include "ofxUI.h"

#include "common.h"

class ofApp : public ofBaseApp
{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    itg::ofxStateMachine<SharedData> mStage;
    
    ofxOculusDK2 mOculus;
    ofxFPSCamera mFPSCam;
    
    ofxPostGlitch mGlitch;
    ofFbo mFbo;
    
    ofxOscReceiver mReceiver;
    
    // toggles
    bool bOculusView;
    bool bFPSMode;
    
    // gui
    vector<ofxUICanvas *> mGui;
    
};
