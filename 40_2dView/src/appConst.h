#pragma once

#define ORIGIN_X ofGetScreenWidth()/2
#define ORIGIN_Y ofGetScreenHeight()/2

// OSCタグ
#define OSCA_SENSOR_PEDAL         "/dsng2/pedal"
#define OSCA_SENSOR_STEER         "/dsng2/steerAngle"
#define OSCA_SENSOR_STEER_RESET   "/dsng2/steerReset"

#define OSCA_RENDERED_DIRECTION   "/dsng2/ctl/dir"
#define OSCA_RENDERED_LOCATION_X  "/dsng2/ctl/px"
#define OSCA_RENDERED_LOCATION_Y  "/dsng2/ctl/py"

// crop 設定
#define DESKTOPCORNER_BEGIN  ofVec2f(0,0)
#define DESKTOPCORNER_END    ofVec2f(ofGetScreenWidth(),ofGetScreenHeight())
//#define DESKTOPCORNER_END    ofVec2f(980,500) // dummy

