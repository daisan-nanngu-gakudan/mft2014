#include "FinderItem.h"

//--------------------------------------------------------------
//
//
FinderItem::FinderItem(const ofVec2f point, string name){
	_p = point;
	_name = name;
}

//--------------------------------------------------------------
//
//
void FinderItem::setup() {
}

//--------------------------------------------------------------
// update
//
//
void FinderItem::update() {

}
//--------------------------------------------------------------
// draw
//  - Finder項目を描画します。
//
void FinderItem::draw() {
    
	ofCircle(_p.x, _p.y, DRAW_SIZE_FINDERITEM_R);

}

//--------------------------------------------------------------
// drawInfo
//  - Finder項目の近傍にテキストで情報表示します。
//
void FinderItem::drawInfo() {

	ofPushStyle();

	ofSetColor(COLOR_DEBUGINFO);

	ofPushMatrix();
	ofTranslate(22, 18); // 画面右上方にオフセット
	ofDrawBitmapString(ofToString(_p.x) + "\n" + ofToString(_p.y), _p.x, _p.y);
	ofPopMatrix();
    
	ofPopStyle();
}
