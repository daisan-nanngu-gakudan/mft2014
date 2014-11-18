#include "FinderItem.h"

//--------------------------------------------------------------
//
//
FinderItem::FinderItem(const ofVec2f point){
    _p = point;
}

//--------------------------------------------------------------
//
//
void FinderItem::setup() {
    
}

//--------------------------------------------------------------
// update
//[design] No any update.
//
void FinderItem::update() {

}
//--------------------------------------------------------------
// draw
//[design] No any update.
//
void FinderItem::draw() {
    
    ofCircle(_p.x, _p.y, ITEM_SIZE_R);
    
}

void FinderItem::drawInfo() {

    ofPushStyle();

    ofSetColor(COLOR_DEBUGINFO);
    ofDrawBitmapString(ofToString(_p.x) + "\n" + ofToString(_p.y), _p.x, _p.y);
    
    ofPopStyle();
    
}

