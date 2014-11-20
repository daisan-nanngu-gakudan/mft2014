#pragma once

// アプリケーションのウィンドウサイズ(ピクセル)
static int winSize[2] = {600, 800};


// メッセージ送信間隔(ミリ秒) [333.3]
//static float sendInterval = 3000.0;
static float sendInterval = 333.3;

// メッセージ送信
#define S_HOST_LOCAL "127.0.0.1"
//#define S_HOST_PC1 "192.168.0.1"
//#define S_HOST_PC2 "192.168.0.2"
#define S_HOST_PC1 "10.0.0.1"
#define S_HOST_PC2 "10.0.0.2"
#define S_PORT_1 12011 // サウンドプレーヤ
#define S_PORT_2 12022 // 2D app
#define S_PORT_3 12033 // 3D app

// メッセージ受信
#define L_PORT 8001
#define NUM_MSG_STRINGS 20

// OSCタグ
#define OSCA_SENSOR_PEDAL "/pedal"
#define OSCA_SENSOR_STEER "/steerAngle"
#define OSCA_SENSOR_STEER_RESET "/steerReset"

// アプリケーションウィンドウに対する、デスクトップフィールドの大きさ
#define WINDOW_DESKTOPFIELD_RATIO 0.55


//
// color schemes
//

static ofColor COLOR_BIKE = ofColor(212, 0, 0);
static ofColor COLOR_TRACK = ofColor(212, 188, 0);

static ofColor COLOR_DEBUGINFO = ofColor(255, 255, 255);

static ofColor COLOR_GUIDE_X = ofColor(188, 0, 0);
static ofColor COLOR_GUIDE_Y = ofColor(0, 188, 0);
static ofColor COLOR_BACKGROUND = ofColor(128, 128, 128);
