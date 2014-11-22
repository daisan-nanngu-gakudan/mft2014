#pragma once

#include "ofMain.h"
#include "ofxState.h"

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
static const string DESKTOP_IMAGE_PATH = "images/desktop.png";



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
    float desktop_width;
    float desktop_height;
    
    float loc_x;
    float loc_y;
};

typedef SharedData shd;
typedef itg::ofxState<SharedData> BaseStage;


#define VALIDE(b) assert(b)
