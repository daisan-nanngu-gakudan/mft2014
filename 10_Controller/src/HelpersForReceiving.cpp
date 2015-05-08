#include "ofApp.h"

//--------------------------------------------------------------
// setupReceiver
// 上位アプリケーションからの受信を待ち受け

void ofApp::setupReceiver(bool flag){

	// 受信モードオフであれば、何もしない
	if (!flag) return;

	receiver.setup(L_PORT);

#if DEBUG
	cout << "listening on [" << L_PORT << "]" << endl;
#endif

}

//--------------------------------------------------------------
// updateReceiver
// - 上位アプリケーションからのメッセージを受信
// - bike モデルに 最新の速さとハンドル角を設定

// Note: 受信メッセージの例
//      /pedal              -- ※ 1回転するごとに bang
//      /steerAngle 0.111   -- ハンドル角 (-1.0 .. 1.0)
//      /steerReset
//
// ForTest: $oscsend localhost 8001 /sample/address iTfs 1 3.14 hello
//          $oscsend localhost 8001 /pedal
//          $oscsend localhost 8001 /steerAngle f 0.1111
//          $oscsend localhost 8001 /steerReset
//
void ofApp::updateReceiver(){
    
	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){ msg_strings[i] = ""; }
	}
  
  // メッセージのハンドリング
	while (receiver.hasWaitingMessages()) {

		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		if (m.getAddress() == OSCA_SENSOR_PEDAL) {

			bike.pedal();

#ifdef DEBUG
			cout  << " received PEDAL" << endl;
#endif
			
		} else if (m.getAddress() == OSCA_SENSOR_STEER) {
            
			float normedSteer = m.getArgAsFloat(0);

			if ( abs(normedSteer) <= 1.0 ) {
				bike.setHandle(normedSteer);
			}
			
#ifdef DEBUG
			cout  << " received STEER[" << normedSteer << "]" << endl;
#endif
			
		} else if (m.getAddress() == OSCA_SENSOR_STEER_RESET) {
			bike.setHandle(0L);

#ifdef DEBUG
			cout  << " received STEER_RESET" << endl;
#endif			
		}
	}
}

//--------------------------------------------------------------
// dumpOSC
// - OSCメッセージをコンソールに出力するユーティリティ関数

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
