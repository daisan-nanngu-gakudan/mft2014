#include "ofApp.h"
#include "ofxKeyPressedDoxygen.h"
#include "MyDesktop.hpp"

void ofApp::setup(){
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
    bOculusView = false;
    bFPSMode = false;

//    ofSetLogLevel( OF_LOG_VERBOSE );
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
    ofxUICanvas * gui = new ofxUICanvas();
    gui->addLabel("COMMON_PARAMETERS", OFX_UI_FONT_MEDIUM);
    gui->addFPS();
    mGui.push_back(gui);
    
    //----------
    // setup post glitch
    //----------
//    assert(mGlitch.setup(&mStage.getSharedData().fbo, "postglitch"));
//    mGlitch.setup(&mFbo, "postglitch");
    mGlitch.setup(&mOculus.getRenderTarget(), "postglitch");
    
}


void ofApp::update()
{
    
    while (mReceiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        mReceiver.getNextMessage(&m);
        
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
    
    mStage.update();
}


void ofApp::draw()
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


void ofApp::keyPressed(int key){
    
    switch (key) {
        case 'f': ofToggleFullscreen(); break; /// toggle fullscreen
        case 'h': bOculusView = !bOculusView; break; /// toggle oculus view/normal view
        
        // test
        case '1': mGlitch.setFxTo("convergence", 0.5); break;
    }

}


void ofApp::keyReleased(int key){

}


void ofApp::mouseMoved(int x, int y ){

}


void ofApp::mouseDragged(int x, int y, int button){

}


void ofApp::mousePressed(int x, int y, int button){

}


void ofApp::mouseReleased(int x, int y, int button){

}


void ofApp::windowResized(int w, int h){

}


void ofApp::gotMessage(ofMessage msg){

}


void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
