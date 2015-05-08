#pragma once
#include <iostream>
#include "ofMain.h"
#include "appConst.h"

// 
// Finder項目 (ファイルやフォルダ)
//
class FinderItem {
    
public:
    ofVec2f _p;
    string _name;
    
    FinderItem(const ofVec2f, string);
    void setup();
    void update();
    void draw();
    void drawInfo();
    
private:

};
