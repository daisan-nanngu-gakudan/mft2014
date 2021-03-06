
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    ofBackground(COLOR_BACKGROUND);
    
    // Window Title for help
    ofSetWindowTitle(ofToString(winSize[0]) +  " " +  ofToString(winSize[1]));
    
    bUseSensor = true;
    bAnimate = true;
    bFade = true;
    bShowMenu = false;
    bNeedSending = true;
    
    desktop.setup(desktopSize);
    
    bike.setup();
    bike.setupCropSettings(ofVec2f(0,0), desktopSize);
    
    // リソースファイル読込
    setupFinderItems();
    
    // 通信のセットアップ - 受信部
    setupReceiver(bUseSensor);

    // 通信のセットアップ - 送信部
    setupSender(true);
    
    collidedItem = -1;
}

//--------------------------------------------------------------
void ofApp::update(){

    // センサを使う場合は、OSC受信メッセージからbikeモデルを更新する
    if (bUseSensor) {
        updateReceiver();
    }
    
    // モデルの更新
    if (bAnimate) bike.update();
    
    // ファイルとの衝突判定
    colition();
    
    // 通信
    updateSender(); // フラグの考慮は呼び出し先でやってくれる
    
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofPushMatrix();
    
	setupSpaces(); // 座標系
	showGuide(); // ガイド

	// Field //
	desktop.draw();
    
	// FinderItems //
	ofPushStyle();
	ofSetColor(COLOR_FINDERITEM);
	
	for (int i=0; i<items.size(); i++){
		items[i].draw();        // アイコン
//		items[i].drawInfo();    // 座標(文字)
	}
	ofPopStyle();
    
	// Bike //
	bike.draw();
	
	ofPopMatrix();
	
	showDebug();
	if(bShowMenu) showMenu();
	ofSetColor(255);
//	ofDrawBitmapString("collided: " + ofToString(collidedItem), 20, 200);
    
#ifdef DEBUG
	// ウィンドウタイトル
	string str = ofToString(ofGetElapsedTimeMillis());
	if (bSendMode) {
		str += "[OSC SendMode ON]";
	}
	ofSetWindowTitle(str);
#endif
	
}

void ofApp::colition()
{
	ofVec2f * bikePos = &bike._location;
	for (int i=0; i<items.size(); i++){
		float diff = items[i]._p.distance(*bikePos);
		if (diff < TH_COLISION)
		{
				collidedItem = i ; // 最初に衝突と判定したファイルのIDを保持
				return;
		}
	}
	collidedItem = -1;
}
