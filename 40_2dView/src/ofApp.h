#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "MousePointer.h"

#define PORT 3001
#define NUM_MSG_STRINGS 20

#define DISP_SIZE_X 320
#define DISP_SIZE_Y 240


class ofApp : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void setupOsc();
    void updateOsc();
    string dumpOSC(ofxOscMessage m);
    
    ofxOscReceiver receiver;
    
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    
    MousePointer mp;  // Mouse Pointer;
    
};

//
// 本アプリが受け取るメッセージの形式
//     速度:  /dsng2/speed float float
//     座標:  /dsng2/position int int
//
// テスト用のコマンド
//  $ oscsend localhost 3001 /dsng2/speed ff 3.12 3.14
//  $ oscsend localhost 3001 /dsng2/position ff 324 661
//
// REQUIRES: サーバプログラム(OSC経由)
//
// 1. 外部アプリケーションから、速度・座標をうけとって
//    マウスを制御します。
//
// 2. ファイルとの接触により、イベントを発火します。
//

