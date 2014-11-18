#pragma once
#include <iostream>
#include "ofMain.h"
#include "appConst.h"

class Desktop {
    
public:
    ofVec2f _size;
    ofVec2f _p;
    
    void setup(const ofVec2f _size);
    void update();
    void draw();
    
    ofVec2f getCornerBegin();
    ofVec2f getCornerEnd();
    
private:
    
};
