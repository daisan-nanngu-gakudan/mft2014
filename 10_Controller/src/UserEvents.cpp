#include "ofApp.h"

//--------------------------------------------------------------
// keyPressed
// - Note: /キーイベントはデバッグ用に設定しています。
//
void ofApp::keyPressed(int key){
    
	fprintf(stdout, "key pressed [%d]\n", key);
    
    switch (key) {
            
            // - - - - - - - - - bike をキー操作で更新 - - - - - - - - - - //
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

            // - - - - - - - - - 動作モード、デバッグコマンド - - - - - - - - - - //
        case ' ':
            bAnimate = !bAnimate;
            break;
        case 'a': // 原点から再開
            bike.setLocation(ofVec2f(0, 0));
            bike.resetHandle();
            bike._speed = 1.0;
            break;
        case '1': // ハンドル角のみ初期化
            bike.resetHandle();
            break;
        case '/': // テスト送信実行
            bNeedSending = true;
            cout << "OSC Sending Toggled to [" << bNeedSending << "]" << endl;
            break;
        case '?':
            bShowMenu = !bShowMenu;
            break;
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
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
