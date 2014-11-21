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
static const float WIDTH  = 1920;
static const float HEIGHT = 1080;



//==========
// osc
//==========
static const int LISTEN_PORT = 12033;




class SharedData
{
public:
};

typedef SharedData shd;
typedef itg::ofxState<SharedData> BaseStage;
