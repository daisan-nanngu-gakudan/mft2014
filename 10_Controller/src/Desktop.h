#pragma once
#include <iostream>
#include "ofMain.h"
#include "appConst.h"

// 
// デスクトップ領域
//
class Desktop {
    
public:
	ofVec2f _size;
	ofVec2f _p;
	ofImage image;
    
	void setup(const ofVec2f _size);
	void update();
	void draw();
    
	ofVec2f getCornerBegin();
	ofVec2f getCornerEnd();
    
private:
    
};
