#pragma onces
#include "ofApp.h"

//--------------------------------------------------------------
// SETUP
//
void ofApp::setupOsc(){
    
    cout << "listening for osc messages on port " << RECV_PORT << "\n";
    
    receiver.setup(RECV_PORT);
    current_msg_string = 0;
}

//--------------------------------------------------------------
//  updateWithOsc // TODO
//
//  テスト用のコマンド
//   $ oscsend localhost 12022 /dsng2/ctl/px f 324
//   $ oscsend localhost 12022 /dsng2/ctl/py f 661
//   $ oscsend localhost 12022 /dsng2/ctl/sp f 1.2
//  -- 以下は没
//   $ oscsend localhost 12022 /dsng2/pedal
//   $ oscsend localhost 12022 /dsng2/steerAngle f 1.0
//   $ oscsend localhost 12022 /dsng2/steerReset

void ofApp::updateWithOsc(){
    
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}
    
	while(receiver.hasWaitingMessages()){

        ofxOscMessage m;
        receiver.getNextMessage(&m);

        // dumpOSC(m);
        
        // 1. OSCによる座標
        if (m.getAddress() == OSCA_RENDERED_LOCATION_X) {

            cout << "OSCA_RENDERED_LOCATION_X" << endl;

            int tmp_x = (int)m.getArgAsFloat(0);
            if (tmp_x) mp._location.x = tmp_x;
            
        } else if (m.getAddress() == OSCA_RENDERED_LOCATION_Y) {
            
            cout << "OSCA_RENDERED_LOCATION_Y" << endl;
            
            int tmp_y = (int)m.getArgAsFloat(0);
            if (tmp_y) mp._location.y = tmp_y;
            
        }
        // TODO : speed
        
        // ここから先は　デッドロジック
        // 理由: これらのタグを送出するのは、
        //       センサーアプリであり、当アプリには直接メッセージを送出しない
        //
        
        // 2. bike model API によるメッセージ
        if (m.getAddress() == OSCA_SENSOR_PEDAL) {
        
            cout  << " received PEDAL" << endl;
            mp.pedal();
        
        } else if (m.getAddress() == OSCA_SENSOR_STEER) {
            
            float normedSteer = m.getArgAsFloat(0);
            cout  << " received STEER[" << normedSteer << "]" << endl;

            if ( abs(normedSteer) <= 1.0 ) {
                mp.setHandle(normedSteer);
            }
            
        } else if (m.getAddress() == OSCA_SENSOR_STEER_RESET) {
            
            cout  << " received STEER_RESET" << endl;
            mp.resetHandle();
        }
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