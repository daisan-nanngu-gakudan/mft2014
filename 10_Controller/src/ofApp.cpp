
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
    bShowMenu = true;
    
    desktop.setup(ofVec2f(1400, 900)); // デスクトップの解像度を入れる
    
    bike.setup();
    bike.setupCropSettings(desktop.getCornerBegin(), desktop.getCornerEnd());
    
    
    // リソースファイル読込
    setupFinderItems();
    
    // 通信のセットアップ - 受信部
    setupReceiver(bUseSensor);

    // 通信のセットアップ - 送信部
//    setupSender(false);
    setupSender(true);
}

//--------------------------------------------------------------
void ofApp::update(){

    // センサを使う場合は、OSC受信メッセージからbikeモデルを更新する
    if (bUseSensor) {
        updateReceiver();
    }
    
    // モデルの更新
    if (bAnimate) bike.update();
    
    // 通信
    updateSender(); // フラグの考慮は呼び出し先でやってくれる
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofPushMatrix();
    
    setupSpaces(); // 座標系
    showGuide(); // ガイド

    // Field
    desktop.draw();
    
    // FinderItems
    ofPushStyle();
    ofSetColor(188);
    for (int i=0; i<items.size(); i++){
        items[i].draw();
        items[i].drawInfo();
    }
    ofPopStyle();
    
    // Bike
	bike.report();
	bike.draw();

    ofPopMatrix();
    
    showDebug();
    if(bShowMenu) showMenu();

    // debug
    ofSetWindowTitle(ofToString(ofGetElapsedTimeMillis()));
}


