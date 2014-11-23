#pragma once

#include "ofMain.h"
#include "common.h"

enum fileItemType { FILE_ITEM_SOUND, FILE_ITEM_MOVIE, FILE_ITEM_TEXT };

static const string ICON_IMAGE_PATH_SOUND = "images/icon_sound.png";
static const string ICON_IMAGE_PATH_TEXT  = "images/icon_text.png";
static const string ICON_IMAGE_PATH_MOVIE = "images/icon_sound.png"; //TODO: change


class FileItem
{
    float mRot;
    float mRand;
    
public:
    ofVec2f mPos;
    fileItemType mType;
    string mFileName;
    ofImage mIconImage;
    
    FileItem(ofVec2f pos, fileItemType type, const string & filename): mPos(pos), mType(type), mFileName(filename)
    {
        switch (mType)
        {
            case FILE_ITEM_SOUND:
                assert(mIconImage.loadImage(ICON_IMAGE_PATH_SOUND));
                break;
            case FILE_ITEM_TEXT:
                assert(mIconImage.loadImage(ICON_IMAGE_PATH_TEXT));
                break;
            case FILE_ITEM_MOVIE:
                assert(mIconImage.loadImage(ICON_IMAGE_PATH_MOVIE));
                break;
        }
        mRot = 0;
        mRand = ofRandom(3);
    }
    
    void update()
    {
//        mRot = ofNoise(ofGetElapsedTimef() * mRand) * 180;
    }
    
    void draw()
    {
        ofPushStyle();
        ofPushMatrix();
        ofEnableDepthTest();
        
        ofTranslate(mPos.x, 10, mPos.y);
        ofRotate(ofGetElapsedTimef() * 30, 0, 1, 0);
        ofSetRectMode(OF_RECTMODE_CENTER);
        mIconImage.draw(0, 0, 0, 100, 100);
        
//        ofSetColor(0, 255, 0);
//        ofCircle(mPos.x, -100, mPos.y, 20);
        ofDrawBitmapString(mFileName, 0, 60, 0);
        
        ofDisableDepthTest();
        ofPopMatrix();
        ofPopStyle();
    }
};
