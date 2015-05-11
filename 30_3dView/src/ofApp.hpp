#pragma once

#include "ofMain.h"
#include "common.h"
#include "FileItem.hpp"

#include "ofxStateMachine.h"
#include "ofxOculusDK2.h"
#include "ofxFPSCamera.h"
#include "ofxOsc.h"
#include "ofxUI.h"
#include "ofxKeyDoc.h"

#include "MyDesktop.hpp"


class ofApp : public ofBaseApp
{
    itg::ofxStateMachine<SharedData> mStage;
    
    // camera
    ofxOculusDK2 mOculus;
    ofxFPSCamera mFPSCam;
    
    // osc
    ofxOscReceiver mReceiver;
    
    // values
    int mrSendCont;
    float mrElapsedTimeLillis;
    float mrBikeSpeed;
    float mrBikeSteer;
    float mrBikeDirection;
    float mEyeHeight;
    ofVec3f mrBikeLocation;
    ofVec3f mManCamPos;
    ofVec3f mManCamOri;
    int mCollidedItem;
    
    // toggles
    bool bDebug;
    bool bOculusView;
    bool bDumpOsc;
    bool bManCamMode;
    
    // controll mode
    enum controllMode { FPS_KEY=0, REMOTE_BIKE } mCtlMode;
    
    // gui
    vector<ofxUICanvas *> mGui;
    
    // window
//    ofVideoGrabber mGrabber;
    
public:
    
    void setup()
    {
        ofSetFrameRate(60);
        ofSetVerticalSync(true);
        ofSetCircleResolution(64);
        //ofSetLogLevel( OF_LOG_VERBOSE );
        
        //----------
        // dump key assigne settings
        //----------
        ofxKeyDoc::read(__FILE__);
        ofxKeyDoc::saveDoc();
        
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
        mCtlMode = REMOTE_BIKE;
        mManCamPos.set(0, 20, 0);
        mManCamOri.set(0, 0, 0);
        mEyeHeight = 30;
        mCollidedItem = -1;
        
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
        mFPSCam.disableMove();
        mOculus.baseCamera = &mFPSCam;
        ofFbo::Settings settings;
        settings.numSamples = 4;
        settings.internalformat = GL_RGBA;
        settings.useDepth = true;
        settings.useStencil = true;
        mOculus.setup(settings);
        
        //----------
        // get file items
        //----------
        getFinderItems(FINDER_ITEM_LIST, mStage.getSharedData().file_items);
        
        
        //----------
        // setup gui
        //----------
        // common canvas
//        ofxUICanvas * gui = new ofxUISuperCanvas("COMMON_PARAMETERS");
        ofxUICanvas * gui = new ofxUIScrollableCanvas(0, 0, 200, ofGetHeight());
        gui->addLabel("PARAMETERS");
        gui->addFPSSlider("FPS");
        
        gui->addSpacer();
        gui->addLabel("TOGGLES");
        gui->addToggle("ENABLE_HMD_VIEW", &bOculusView);
        gui->addToggle("DUMP_OSC", &bDumpOsc);
        
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
        gui->add2DPad("LOCATION", ofVec2f(0, DESKTOP_WIDTH), ofVec2f(0, DESKTOP_HEIGHT), &mrBikeLocation);
        gui->addRotarySlider("DIRECTION", 0.0, TWO_PI, &mrBikeDirection);
        gui->addSlider("EYE_HEIGHT", 0, 120, &mEyeHeight);
        
        gui->addSpacer();
        gui->addLabel("MANUAL_CAMERA");
        gui->addToggle("MANUAL_CAMERA", &bManCamMode);
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
                if (m.getAddress() == "/dsng2/ctl/st") // ハンドル角 (-1.0 〜 1.0), float
                {
                    mrBikeSteer = m.getArgAsFloat(0);
                }
                if (m.getAddress() == "/dsng2/ctl/dir") // 方角 0-360, float
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
                if (m.getAddress() == "/dsng2/ctl/collide")
                {
                    mCollidedItem = m.getArgAsInt32(0);
                }
            }
        }
        
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
                mrBikeDirection = ofDegToRad(mFPSCam.getOrientationEuler().y) + PI;
            }
            else if (mCtlMode == REMOTE_BIKE)
            {
                mFPSCam.setPosition(mrBikeLocation.x, mEyeHeight, mrBikeLocation.y);
                ofVec3f rot = mFPSCam.getOrientationEuler();
                mFPSCam.setOrientation(ofVec3f(rot.x, ofRadToDeg(-mrBikeDirection), rot.z));
            }
        }
        
        //----------
        // update stage
        //----------
        mStage.update();
        
        //----------
        // corition files
        //----------
//        item_it it = mStage.getSharedData().file_items.begin();
//        while (it != mStage.getSharedData().file_items.end())
//        {
//            (*it)->draw();
//            ++it;
//        }
        
    }
    
    
    void draw()
    {
        ofBackground(0, 0, 0);
        ofSetColor(255);
        
        if(mOculus.isSetup() && bOculusView)
        {
            //==========
            // draw over view
            //==========
            if(mCollidedItem != -1) mStage.getSharedData().file_items[mCollidedItem]->play();
            
            mOculus.beginOverlay(-230, 320,240);
            ofRectangle overlayRect = mOculus.getOverlayRectangle();
            
            
            ofPushStyle();
            ofEnableAlphaBlending();
//            ofFill();
//            ofSetColor(0, 180);
//            ofRect(overlayRect);
            
            //----------
            // draw file event
            //----------
            item_it it = mStage.getSharedData().file_items.begin();
            while (it != mStage.getSharedData().file_items.end())
            {
                (*it)->drawEvent(320, 240);
                ++it;
            }
            
            ofPopStyle();
            mOculus.endOverlay();
            
            
            //==========
            // draw main view
            //==========
            ofSetColor(255);
            mOculus.beginLeftEye();
            mStage.draw();
            mOculus.endLeftEye();
            mOculus.beginRightEye();
            mStage.draw();
            mOculus.endRightEye();
            mOculus.draw();
        } else {
            mFPSCam.begin();
            mStage.draw();
            mFPSCam.end();
        }
        
        
        if (bManCamMode)
        {
            ofSetColor(255, 0, 0);
            ofDrawSphere(mrBikeLocation.x, mEyeHeight, mrBikeLocation.y, 25);
        }
        
        
        //----------
        // draw info
        //----------
        if (bDebug)
        {
            stringstream s;
            s << ofxKeyDoc::getDoc() << endl;
            s << "file items" <<  endl;
            for (int i = 0; i < mStage.getSharedData().file_items.size(); ++i) s << i << " " << mStage.getSharedData().file_items[i]->getPos() << endl;
            s << "collision: " << mCollidedItem << endl;
            ofSetColor(255);
            ofDrawBitmapString(s.str(), mGui[0]->getRect()->getMaxX() + 20, mGui[0]->getRect()->getMinY() + 10);
        }
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
            if (tog->getValue() == 1)
            {
                mFPSCam.disableMove();
            } else {
                mFPSCam.enableMove();
            }
        }
    }
    
    
    void getFinderItems(const string & filename, vector<FileItem *> & file_items)
    {

        ofBuffer buffer = ofBufferFromFile(filename);
        if(buffer.size())
        {
            file_items.clear();
            while(buffer.isLastLine() == false)
            {
                
                string line = buffer.getNextLine();
                
                if(line.empty() == false)
                {
                    vector<string> words = ofSplitString(line, " ");
                    vector<string> filename = ofSplitString(words[2], ".");
                    
                    float x = ofToFloat(words[3]);
                    float y = ofToFloat(words[4]);
                    ofVec2f pos(x, y);

#ifdef DUMMY_ICON_MODE
                    
                    file_items.push_back(new TempIcon(pos, words[2]));
                    
#else
                    
                    if (filename.back() == "aif") file_items.push_back(new SoundFile(pos, words[2]));
                    if (filename.back() == "txt") file_items.push_back(new TextFile(pos, words[2]));
                    //if (filename.back() == "mov") //TODO: make movie file

#endif
                }
            }
        }
        
        // debug info
        ofLogNotice() << "FinderItems size:" << file_items.size();
        for (int i=0; i<file_items.size(); i++) {
            ofLogNotice() << "item[" << i << "] " << file_items[i]->getPos().x << ":" << file_items[i]->getPos().y;
        }
    }
    
};
