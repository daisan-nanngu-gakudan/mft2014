#include "ofApp.h"

//--------------------------------------------------------------
// setupSender
// - クライアントとの通信系を構築します。
// - Note: 宛先は固定です。

void ofApp::setupSender(bool flag){
    
    // フラグの初期化
    bSendMode = flag;
    _prevSendTime = ofGetElapsedTimeMillis();
    
    if (!bSendMode) {
        // 送信オフ
        cout << "setupSender....NO --- No use clients." << endl;
        return;
        
    } else {
        // 送信オン
        cout << "setupSender...YES" << endl;
        
        // ofxOSCの初期化
        // 宛先は3つ。
//        senders[0].setup("127.0.0.1", 12011);
//        senders[1].setup("127.0.0.1", 12022);
//        senders[2].setup("127.0.0.1", 12033);
        senders[0].setup(S_HOST_LOCAL, S_PORT_1); // サウンドプレーヤ
        senders[1].setup(S_HOST_LOCAL, S_PORT_2); // 2D app
        senders[2].setup(S_HOST_PC2, S_PORT_3); // 3D app
        // TODO : 接続時の例外処理
    }
}

//--------------------------------------------------------------
// updateSender
// - クライアントとの通信を更新します。
// - Note: 宛先は固定です。

void ofApp::updateSender(){
    
    // 送信モードかつ、送信対象メッセージありの時のみ送信
    if (bSendMode && bNeedSending) {
        
        // 送信タイミングの調整。
        // 所定インターバルを経過していれば送信する。
        if (ofGetElapsedTimeMillis() > _prevSendTime + sendInterval ){
        
            _prevSendTime = ofGetElapsedTimeMillis();

            cout << "send!" << endl;
            send();
            
            // 後始末 - 1回ぽっきりで送信を抑止する場合はコメントアウトする。
            // bNeedSending = false;
        }
    }
}

//--------------------------------------------------------------
// send
// - クライアントとの通信をおこないます。
// - Note: 宛先は固定です。
// - TODO: OSCバンドルするべき？

void ofApp::send(){
    
    // メッセージ作成
    ofxOscMessage m0, m1, m2, m3, m4, m5;
    m0.setAddress("/dsng2/ctl/FRAMEINFO"); // 送信回次 int, 時刻 float
    m1.setAddress("/dsng2/ctl/sp");  // 速さ(スカラー量), float
    m2.setAddress("/dsng2/ctl/st");  // ハンドル角 (-1.0 〜 1.0), float
    m3.setAddress("/dsng2/ctl/dir"); // 方角 0-360, float
    m4.setAddress("/dsng2/ctl/px");  // 位置.x座標 , float
    m5.setAddress("/dsng2/ctl/py");  // 位置.y座標, float
    
    m0.addIntArg(_sendCount++);
    m0.addFloatArg(ofGetElapsedTimeMillis());
    m1.addFloatArg(bike._speed);
    m2.addFloatArg(bike._steer);
    m3.addFloatArg(bike._direction);
    m4.addFloatArg(bike._location.x);
    m5.addFloatArg(bike._location.y);
    
    // 各宛先に送信
    for (int i =0; i<3; i++) {
        senders[i].sendMessage(m0);
        senders[i].sendMessage(m1);
        senders[i].sendMessage(m2);
        senders[i].sendMessage(m3);
        senders[i].sendMessage(m4);
        senders[i].sendMessage(m5);
    }
}


