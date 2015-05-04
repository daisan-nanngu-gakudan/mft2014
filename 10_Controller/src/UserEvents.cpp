#include "ofApp.h"
//
//--------------------------------------------------------------
// keyPressed
//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    
	fprintf(stdout, "key pressed [%d]\n", key);
    
	switch (key) {

			// bike の操作
			case OF_KEY_UP:
				bike.pedal();
				break;
			case OF_KEY_DOWN:
				bike.stop();
				break;
			case OF_KEY_LEFT:
				bike.handle(-0.1);
				break;
			case OF_KEY_RIGHT:
				bike.handle(+0.1);
				break;

			// モード制御
			case ' ': // アニメーション
				bAnimate = !bAnimate;
				break;
			case 'a': // 原点から再スタート
				bike.setLocation(ofVec2f(0, 0));
				bike.resetHandle();
				bike._speed = 1.0;
				break;
			case 's':	// OSC送信のON/OFF
				bSendMode = !bSendMode;
				break;
			case '1': // ハンドル角のリセット
				bike.resetHandle();
				break;
			case '/': // OSCメッセージテスト送信
				bNeedSending = true;
				cout << "OSC Sending Toggled to [" << bNeedSending << "]" << endl;
				break;
			case 'd': // OSCメッセージテスト送信
				sendItems();
				break;
			case '?':
				// bShowMenu = !bShowMenu;
				ofToggleFullscreen();
				break;
			default:
				break;
	}
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
