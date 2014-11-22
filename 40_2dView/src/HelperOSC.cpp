#pragma onces
#include "ofApp.h"

//--------------------------------------------------------------
// SETUP
//
void ofApp::setupOsc(){
    
    cout << "listening for osc messages on port " << RECV_PORT << "\n";
    receiver.setup(RECV_PORT);
    
    current_msg_string = 0;
    mouseX = 0;
    mouseY = 0;
    
    ofBackground(30, 30, 130);
}

//--------------------------------------------------------------
// UPDATE
//
void ofApp::updateWithOsc(){
	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}
    
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);

        if (m.getAddress() == OSCA_SENSOR_PEDAL) {
        
            cout  << " received PEDAL" << endl;
            
            mp.pedal();
        
        } else if (m.getAddress() == OSCA_SENSOR_STEER) {
            
            float normedSteer = m.getArgAsFloat(0);
            cout  << " received STEER[" << normedSteer << "]" << endl;

            // モデルの更新
            // TODO: チューニング
            if ( abs(normedSteer) <= 1.0 ) {
                mp.setHandle(normedSteer);
            }
            
        } else if (m.getAddress() == OSCA_SENSOR_STEER_RESET) {
            
            cout  << " received STEER_RESET" << endl;
            
            // モデルの更新
            mp.resetHandle();
            
        }
            
            
        //
        // pedal, steer
        // process for Mouse Pointer
        //

        dumpOSC(m);
    }
    

    
}

//--------------------------------------------------------------
// OSCメッセージをコンソールに出力する関数
//
string ofApp::dumpOSC(ofxOscMessage m) {
	string str = m.getAddress();
	for (int i=0; i<m.getNumArgs(); i++ ) {
		str += " ";
		switch (m.getArgType(i)) {
			case OFXOSC_TYPE_INT32:
				str += ofToString( m.getArgAsInt32(i));
				break;
			case OFXOSC_TYPE_FLOAT:
				str += ofToString( m.getArgAsFloat(i));
				break;
			case OFXOSC_TYPE_STRING:
				str += m.getArgAsString(i);
				break;
			default:
				break;
		}
	}
	cout << str << endl;
	return str;
}