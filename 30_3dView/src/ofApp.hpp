#pragma once

#include "ofMain.h"
#include "common.h"
#include "ofxStateMachine.h"
#include "ofxOculusDK2.h"
#include "ofxPostGlitch.h"
#include "ofxFPSCamera.h"
#include "ofxOsc.h"
#include "ofxUI.h"
#include "ofxKeyPressedDoxygen.h"

#include "MyDesktop.hpp"


class ofApp : public ofBaseApp
{
    itg::ofxStateMachine<SharedData> mStage;
    
    ofxOculusDK2 mOculus;
    ofxFPSCamera mFPSCam;
    
    ofxPostGlitch mGlitch;
    ofFbo mFbo;
    
    ofxOscReceiver mReceiver;
    
    // toggles
    bool bDebug;
    bool bOculusView;
    bool bFPSMode;
    bool bDumpOsc;
    
    // gui
    vector<ofxUICanvas *> mGui;
    
public:
    
    void setup()
    {
        ofSetFrameRate(60);
        ofSetVerticalSync(true);
        
        //----------
        // dump key assigne settings
        //----------
        ofxKeyPressedDoxygen::read(__FILE__);
        ofxKeyPressedDoxygen::saveDoc();
        
        //----------
        // setup osc
        //----------
        mReceiver.setup(LISTEN_PORT);
        
        //----------
        // init values
        //----------
        bDebug = true;
        bOculusView = false;
        bFPSMode = false;
        bDumpOsc = true;
        
        //ofSetLogLevel( OF_LOG_VERBOSE );
        //----------
        // setup stages
        //----------
        mStage.addState<MyDesktop>();
        mStage.changeState(STAGE_00);
        mStage.disableAppEvents();
        
        //----------
        // setup oculus
        //----------
        mFPSCam.setup();
        //    mFPSCam.usemouse = false;
        mFPSCam.setCamHeight(10);
        mFPSCam.target(ofVec3f(1,0,0));
        mOculus.baseCamera = &mFPSCam;
        mOculus.setup();
        
        //----------
        // setup shared data
        //----------
        ofFbo::Settings s;
        s.width = mOculus.getRenderTarget().getWidth();
        s.height = mOculus.getRenderTarget().getHeight();
        s.useDepth = true;
        s.useStencil = true;
        s.internalformat = GL_RGBA;
        mFbo.allocate(s);
        
        //----------
        // setup gui
        //----------
        // common canvas
        ofxUICanvas * gui = new ofxUISuperCanvas("COMMON_PARAMETERS");
        gui->addSpacer();
        gui->addFPSSlider("FPS");
        gui->addSpacer();
        gui->addLabel("TOGGLES");
        gui->addToggle("ENABLE_HMD_VIEW", &bOculusView);
        gui->addToggle("ENABLE_FPS_CONTROLL", &bFPSMode);
        gui->addToggle("DUMP_OSC", &bDumpOsc);
        ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
        mGui.push_back(gui);
        
        for (int i = 0; i < mGui.size(); ++i)
        {
            mGui[i]->loadSettings("settings_" + ofToString(i) + ".xml");
        }
        
        //----------
        // setup post glitch
        //----------
        //assert(mGlitch.setup(&mStage.getSharedData().fbo, "postglitch"));
        //mGlitch.setup(&mFbo, "postglitch");
        mGlitch.setup(&mOculus.getRenderTarget(), "postglitch");
        
    }
    
    
    void update()
    {
        
        //==========
        // receive osc
        //==========
        while (mReceiver.hasWaitingMessages())
        {
            ofxOscMessage m;
            mReceiver.getNextMessage(&m);
            
            //----------
            // dump message
            //----------
            if (bDumpOsc)
            {
                cout << m.getAddress() << " ";
                for (int i = 0; i < m.getNumArgs(); i++)
                {
                    switch (m.getArgType(i))
                    {
                        case OFXOSC_TYPE_INT32:  cout << m.getArgAsInt32(i); break;
                        case OFXOSC_TYPE_FLOAT:  cout << m.getArgAsFloat(i); break;
                        case OFXOSC_TYPE_STRING: cout << m.getArgAsString(i); break;
                        default: cout << "[unknown type]" << m.getArgAsString(i); break;
                    }
                    cout << " ";
                }
                cout << endl;
            }
            
            
        }
        
        mStage.update();
    }
    
    
    void draw()
    {
        
        ofBackground(0);
        ofSetColor(255);
        
        if(mOculus.isSetup() && bOculusView)
        {
            
            //		if(showOverlay)
            //        {
            //        }
            
            ofSetColor(255);
            glEnable(GL_DEPTH_TEST);
            mOculus.beginLeftEye();
            mStage.draw();
            mOculus.endLeftEye();
            mOculus.beginRightEye();
            mStage.draw();
            mOculus.endRightEye();
            mGlitch.generateFx();
            mOculus.draw();
            glDisable(GL_DEPTH_TEST);
        } else {
            mFPSCam.begin();
            mStage.draw();
            mFPSCam.end();
        }
        
        stringstream s;
        s << ofxKeyPressedDoxygen::getDoc() << endl;
        ofDrawBitmapStringHighlight(s.str(), mGui[0]->getRect()->getMaxX() + 20, mGui[0]->getRect()->getMinY() + 10);
    }
    
    void exit()
    {
        for (int i = 0; i < mGui.size(); ++i)
        {
            mGui[i]->saveSettings("settings_" + ofToString(i) + ".xml");
        }
    }
    
    
    void keyPressed(int key){
        
        switch (key) {
            case 'F': ofToggleFullscreen(); break; /// toggle fullscreen
            case 'H': bOculusView = !bOculusView; break; /// toggle oculus view/normal view
            case 'D': bDebug = !bDebug; mGui[0]->setVisible(bDebug); break; /// toggle debug mode
                
            // test
            case '1': mGlitch.setFxTo("convergence", 0.5); break;
        }
        
    }
    
    
    void keyReleased(int key){}
    void mouseMoved(int x, int y ){}
    void mouseDragged(int x, int y, int button){}
    void mousePressed(int x, int y, int button){}
    void mouseReleased(int x, int y, int button){}
    void windowResized(int w, int h){}
    void gotMessage(ofMessage msg){}
    void dragEvent(ofDragInfo dragInfo){}
    
    
    
    void guiEvent(ofxUIEventArgs &e)
    {
        if (e.getName() == "ENABLE_FPS_CONTROLL")
        {
            ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
            bool res = toggle->getValue();
            if (res) {
                mFPSCam.enableMove();
                mFPSCam.enableStrafe();
            } else {
                mFPSCam.disableMove();
                mFPSCam.disableStrafe();
            }
        }
    }
    
};
