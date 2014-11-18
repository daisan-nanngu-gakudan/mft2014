#pragma once
#include <iostream>
#include "ofMain.h"
#include "appConst.h"

#define ITEM_SIZE_R 10 // drawing size

class FinderItem {
    
public:
    ofVec2f _p;
    
    FinderItem(const ofVec2f);
    void setup();
    void update();
    void draw();
    void drawInfo();
    
private:

};
