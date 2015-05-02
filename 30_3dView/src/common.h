#pragma once

#include "ofMain.h"
#include "FileItem.hpp"
#include "ofxState.h"
#include "SharedDataReceiver.hpp"

//==========
// stage name
//==========
static const string STAGE_00 = "MyStage";



//==========
// hmd window size
//==========
static const float HMD_WIDTH  = 1920;
static const float HMD_HEIGHT = 1080;


//==========
// desktop size
//==========
static const float DESKTOP_WIDTH  = 1400;
static const float DESKTOP_HEIGHT = 900;


//==========
// osc
//==========
static const int LISTEN_PORT = 12033;



//==========
// deta
//==========
static const string DESKTOP_IMAGE_PATH = "images/desktop.jpg";
static const string FINDER_ITEM_LIST = "finderItems.txt";



//==========
// from taniguchi
//==========

// #define PICT "desktop.jpg" // FPS 7-8とかになる
#define BOOM_UNIT 5
#define PAN_UNIT 10
#define SPEED_UNIT 0.10

#define INIT_SPEED 2
#define INIT_CAM_POS_Z 25

#define FIELD_AMPLIFY 7 // default 1
// 縦横10倍, - ちょっと広い
// 縦横 7倍, - いい感じ。 30〜40秒で一周
#define WRAP_OFFSET 0



class SharedData
{
public:
    vector<FileItem *> file_items;
    SharedDataReceiver mmdReceiver;
};

typedef SharedData shd;
typedef itg::ofxState<SharedData> BaseStage;
typedef vector<FileItem *>::iterator item_it;

#define VALIDE(b) assert(b)


//==========
// utils
//==========
#define debugMouseX(a) (((float)ofGetMouseX()/(float)ofGetWidth())*a)
#define debugMouseY(a) (((float)ofGetMouseY()/(float)ofGetHeight())*a)

// aよりbが大きければb-aを返す（変数更新時のリミッター用）
#define	MIN_NORM(a,b) (((a)<(b))?(a):(b-a))

// 画面中心を取得
#define CENTER_X (ofGetWidth()/2)
#define CENTER_Y (ofGetHeight()/2)


// 処理速度の計測
static clock_t start = 0;
#define START_CLOCK (start = clock())
#define GET_CLOCK (clock()-start)
#define PRINT_CLOCK(comment) (std::cout<<comment<<clock()-start<<std::endl)


// ofLogger utils
#define LOG_INFO ofToString(ofGetElapsedTimeMillis(),8)
#define LOG_NOTICE ofLogNotice(LOG_INFO)
#define LOG_ERROR ofLogError(LOG_INFO)
#define LOG_WARNING ofLogWarning(LOG_INFO)

#define MY_CHECK(e) assert(e)

