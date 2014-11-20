#include "ofApp.h"

//--------------------------------------------------------------
// setupSpaces
// - 描画時に必要な、座標系の変換をおこないます。

void ofApp::setupSpaces(){
    ofTranslate(ofGetWidth()/2.0, ofGetHeight()/2.0, 0);
    ofRotate(-90);
    
//    ofScale(1, 1);
    ofScale(WINDOW_DESKTOPFIELD_RATIO, WINDOW_DESKTOPFIELD_RATIO);
}


//--------------------------------------------------------------
// showDebug
// - デバッグ情報を表示します
//   1.スピード
//   2.ハンドル角(-1.0 - 1.0)
//   3.方角(ラジアン値)
//   4.位置

void ofApp::showDebug(){
    
    // メソッド内のローカルな計算
    Bike *b = &bike;
    float sp = b->_speed;
    float st = b->_steer;
    
    stringstream s1, s2, s3, s4;
    
    // speed
    s1 << "speed     :  " << ofToString(sp, 2) << "    ";
    for (int i = 0 ; i < 40; i++) s1 << (sp * 10 > i ? '*' : '-') ;
    
    // steer
    int stRounded = round( ofMap(st, -1, 1, 0, 20) );
    s2 << "steer     : " << (st < 0 ?'-':' ')
                        << ofToString(abs(st), 2) << "    ";
    for (int i = 0 ; i < 21; i++) s2 << (stRounded == i ? '|' : '-') ;
    
    
    //  direction (radian)
    s3 << "direction : " << (b->_direction < 0 ?'-':' ')
                         << ofToString(abs(b->_direction), 2)  << endl;
    s4 << "position  : " << (b->_location.x < 0 ?'-':' ')
                         <<  ofToString(abs(b->_location.x), 0) << ", "
                         << (b->_location.y < 0 ?'-':' ')
                         <<  ofToString(abs(b->_location.y), 0) << endl;
    
    // desktop size info
    stringstream s5, s6;
    s5 << "Desktop Size : " << desktop._size.x << ", "
                            << desktop._size.y << endl;
    s6 << "Desktop Pos  : " << desktop._p.x << ", "
                            << desktop._p.y << endl;
    
    
    ofPushStyle();
    ofSetColor(COLOR_DEBUGINFO);
    ofDrawBitmapString(s1.str(), 20, 20);   // speed
    ofDrawBitmapString(s2.str(), 20, 36);   // steer -1..1.
    ofDrawBitmapString(s3.str(), 20, 52);   // dir(rad)
    ofDrawBitmapString(s4.str(), 20, 68);   // position (x,y)
    
    ofDrawBitmapString(s5.str(), 20, 84);   // size (x,y)
    ofDrawBitmapString(s6.str(), 20, 100);  // position (x,y)
    ofPopStyle();
    
}

//--------------------------------------------------------------
// showMenu
// - 座標系を表現するガイドを表示します
// - X, Y軸の正方向を太線とする

void ofApp::showMenu(){
    stringstream s1;

    s1 <<      "KEYS / / / / / / / / / / / / / / / / / / / "
    << endl << "    SPACE . " "Ticks on/off"
    << endl << "     DOWN . " "Stop the bike."
    << endl << "        a . " "Restarts the bike with the origin."
    << endl << "        1 . " "Reset steer."
    << endl << "        / . " "OSC test send."
    << endl << "        ? . " "Show/hide this Menu."
    << endl << "/ / / / / / / / / / / / / / / / / / / / / / "
    << endl;
    
    ofDrawBitmapString(s1.str(), ofGetWidth()/2-165, 140);
}


//--------------------------------------------------------------
// showGuide
// - 座標系を表現するガイドを表示します
// - X, Y軸の正方向を太線とする

void ofApp::showGuide(){
    
    float scale = 1000;
    
    ofPushStyle();
    
    ofSetColor(COLOR_GUIDE_X);
    ofSetLineWidth(1.0);   ofLine(-scale, 0, scale, 0);
    ofSetLineWidth(3.0);   ofLine(0, 0, scale, 0);
    
    ofSetColor(COLOR_GUIDE_Y);
    ofSetLineWidth(1.0);   ofLine(0, -scale, 0, scale);
    ofSetLineWidth(3.0);   ofLine(0, 0, 0, scale);
    
    ofPopStyle();
}

//--------------------------------------------------------------
// setupFinderItems
// - txtを読み込んで、ofVec2f(FinderItem座標)のリストを構築します
//
// IN形式: /dump 2 23649_loofa_A_005.aif 189 202
//         任意の複数行(0〜N)

void ofApp::setupFinderItems(){

    // file -> buffer
    ofBuffer buffer = ofBufferFromFile("finderItems.txt");
    
    // buffer -> vec2f
    if(buffer.size()) {
        while(buffer.isLastLine() == false) {
            
            string line = buffer.getNextLine();
            
            if(line.empty() == false) {
                vector<string> words = ofSplitString(line, " ");
                FinderItem tmpItem = FinderItem(ofVec2f(ofToFloat(words[3]), ofToFloat(words[4])));
                items.push_back(tmpItem);
            }
        }
    } // load end

    // debug info
    cout << "FinderItems size:" << items.size() << endl;
    for (int i=0; i<items.size(); i++) {
        cout << "item[" << i << "] " << items[i]._p.x << ":" << items[i]._p.y << endl;
    }
}
