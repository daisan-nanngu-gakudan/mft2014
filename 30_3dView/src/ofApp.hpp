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
    
    // camera
    ofxOculusDK2 mOculus;
    ofxFPSCamera mFPSCam;
    
    // post glitch
    ofxPostGlitch mGlitch;
    
    // osc
    ofxOscReceiver mReceiver;
    
    // values
    int mrSendCont;
    float mrElapsedTimeLillis;
    float mrBikeSpeed;
    float mrBikeSteer;
    float mrBikeDirection;
    ofVec3f mrBikeLocation;
    ofVec3f mManCamPos;
    ofVec3f mManCamOri;
    
    
    // toggles
    bool bDebug;
    bool bOculusView;
    bool bDumpOsc;
    bool bManCamMode;
    
    // controll mode
    enum controllMode { FPS_KEY=0, REMOTE_BIKE } mCtlMode;
    
    // gui
    vector<ofxUICanvas *> mGui;
    
public:
    
    void setup()
    {
        ofSetFrameRate(60);
        ofSetVerticalSync(true);
        ofSetCircleResolution(64);
        
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
        bDumpOsc = true;
        mCtlMode = FPS_KEY;
        mManCamPos.set(0, 10, 0);
        mManCamOri.set(0, 0, 0);
        
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
        mFPSCam.camHeight = 10;
        mFPSCam.target(ofVec3f(1,0,0));
        mOculus.baseCamera = &mFPSCam;
        mOculus.setup();
        
        //----------
        // setup shared data
        //----------
        mStage.getSharedData().desktop_width  = 0;
        mStage.getSharedData().desktop_height = 0;
        mStage.getSharedData().loc_x = 0;
        mStage.getSharedData().loc_y = 0;
        
        
        //----------
        // setup gui
        //----------
        // common canvas
//        ofxUICanvas * gui = new ofxUISuperCanvas("COMMON_PARAMETERS");
        ofxUICanvas * gui = new ofxUIScrollableCanvas(0, 0, 200, ofGetHeight());
        gui->addSpacer();
        gui->addFPSSlider("FPS");
        
        gui->addSpacer();
        gui->addLabel("TOGGLES");
        gui->addToggle("ENABLE_HMD_VIEW", &bOculusView);
        gui->addToggle("DUMP_OSC", &bDumpOsc);
        gui->addToggle("MANUAL_CAMERA", &bManCamMode);
        
        gui->addSpacer();
        gui->addLabel("CONTROLL_MODE");
        vector<string> names;
        names.push_back("FPS_KEY");
        names.push_back("REMOTE_BIKE");
        gui->addRadio("SELECT_MODE", names, OFX_UI_ORIENTATION_VERTICAL);
        
        gui->addSpacer();
        gui->addLabel("BIKE_STATUS");
        gui->addSlider("STEER", -1.0, 1.0, &mrBikeSteer);
        gui->addSlider("SPEED", 0.0, 4.0, &mrBikeSpeed);
        gui->add2DPad("LOCATION",
                      ofVec2f(-(DESKTOP_WIDTH*0.5), DESKTOP_WIDTH*0.5),
                      ofVec2f(-(DESKTOP_HEIGHT*0.5), DESKTOP_HEIGHT*0.5), &mrBikeLocation);
        gui->addRotarySlider("DIRECTION", 0.0, TWO_PI, &mrBikeDirection);
        
        gui->addSpacer();
        gui->addLabel("MANUAL_CAMERA_CONTROLL");
        gui->addSlider("POS_X", -2000, 2000, &mManCamPos.x);
        gui->addSlider("POS_Y", -2000, 2000, &mManCamPos.y);
        gui->addSlider("POS_Z", -2000, 2000, &mManCamPos.z);
        gui->addSlider("ORI_X", -180, 180, &mManCamOri.x);
        gui->addSlider("ORI_Y", -180, 180, &mManCamOri.y);
        gui->addSlider("ORI_Z", -180, 180, &mManCamOri.z);
        
        gui->autoSizeToFitWidgets();
        ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
        mGui.push_back(gui);
        
        for (int i = 0; i < mGui.size(); ++i)
        {
            mGui[i]->loadSettings("settings_" + ofToString(i) + ".xml");
        }
        
        //----------
        // setup post glitch
        //----------
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
            
            //----------
            // get value
            //----------
            if (mCtlMode == REMOTE_BIKE)
            {
                if (m.getAddress() == "/dsng2/ctl/FRAMEINFO")
                {
                    mrSendCont = m.getArgAsInt32(0);
                    mrElapsedTimeLillis = m.getArgAsFloat(1);
                }
                if (m.getAddress() == "/dsng2/ctl/sp")
                {
                    mrBikeSpeed = m.getArgAsFloat(0);
                }
                if (m.getAddress() == "/dsng2/ctl/st")
                {
                    mrBikeSteer = m.getArgAsFloat(0);
                }
                if (m.getAddress() == "/dsng2/ctl/dir")
                {
                    mrBikeDirection = m.getArgAsFloat(0);
                }
                if (m.getAddress() == "/dsng2/ctl/px")
                {
                    mrBikeLocation.x = m.getArgAsFloat(0);
                }
                if (m.getAddress() == "/dsng2/ctl/py")
                {
                    mrBikeLocation.y = m.getArgAsFloat(0);
                }
            }
        }
        
        //----------
        // update shared data
        //----------
        mStage.getSharedData().loc_x = mrBikeLocation.x;
        mStage.getSharedData().loc_x = mrBikeLocation.y;
        
        //----------
        // update camera
        //----------
        if (bManCamMode)
        {
            mFPSCam.setPosition(mManCamPos);
            mFPSCam.setOrientation(mManCamOri);
        }
        else {
            if (mCtlMode == FPS_KEY)
            {
                ofVec3f cur = mFPSCam.getPosition();
                mrBikeLocation.set(cur.x, cur.z);
                mrBikeDirection = ofDegToRad(mFPSCam.getOrientationEuler().y - 180.0);
            }
            else if (mCtlMode == REMOTE_BIKE) {
                ofVec3f cur = mFPSCam.getPosition();
                mFPSCam.setPosition(mrBikeLocation.x, cur.y, mrBikeLocation.y);
                ofVec3f rot = mFPSCam.getOrientationEuler();
                //TODO: camera rotation from bike
                mFPSCam.setOrientation(ofVec3f(rot.x, ofRadToDeg(-mrBikeDirection) - 90.0, rot.z));
            }
        }
        
        //----------
        // update stage
        //----------
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
        ofDrawBitmapString(s.str(), mGui[0]->getRect()->getMaxX() + 20, mGui[0]->getRect()->getMinY() + 10);
    }
    
    void exit()
    {
        for (int i = 0; i < mGui.size(); ++i)
        {
            mGui[i]->saveSettings("settings_" + ofToString(i) + ".xml");
        }
    }
    
    
    void keyPressed(int key)
    {
        switch (key) {
            case 'F': ofToggleFullscreen(); break; /// toggle fullscreen
            case 'H': bOculusView = !bOculusView; break; /// toggle oculus view/normal view
            case 'D': bDebug = !bDebug; mGui[0]->setVisible(bDebug); break; /// toggle debug mode
            case 'C': bManCamMode = !bManCamMode; break; /// toggle manual camera
                
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
        if (e.getName() == "SELECT_MODE")
        {
            ofxUIRadio * rad = (ofxUIRadio *) e.widget;
            mCtlMode = static_cast<controllMode>(rad->getValue());
            
            mCtlMode == FPS_KEY ? mFPSCam.enableMove() : mFPSCam.disableMove();
        }
        
        if (e.getName() == "MANUAL_CAMERA")
        {
            ofxUIToggle * tog = (ofxUIToggle *) e.widget;
            tog->getValue() == 1 ? mFPSCam.enableMove() : mFPSCam.disableMove();
        }
    }
    
};
