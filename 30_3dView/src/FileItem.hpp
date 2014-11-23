#pragma once

#include "ofMain.h"
#include "common.h"

enum fileItemType { FILE_ITEM_SOUND, FILE_ITEM_MOVIE, FILE_ITEM_TEXT };

static const string ICON_IMAGE_PATH_SOUND = "images/icon_sound.png";
static const string ICON_IMAGE_PATH_TEXT  = "images/icon_text.png";
static const string ICON_IMAGE_PATH_MOVIE = "images/icon_sound.png"; //TODO: change

static const string ITEM_PATH_ROOT = "items/";

class FileItem
{
    
    
    // real data
    ofSoundPlayer mSound;
//    ofVideoPlayer mVideo;
    vector<string> mText;
    
    int nBandsToGet;
    float * fftSmoothed;
    
    int mLineCount;
    
public:
    ofVec2f mPos;
    fileItemType mType;
    string mFileName;
    ofImage mIconImage;
    bool bPlay;
    
    FileItem(ofVec2f pos, fileItemType type, const string & filename): mPos(pos), mType(type), mFileName(filename)
    {
        switch (mType)
        {
            case FILE_ITEM_SOUND:
                assert(mIconImage.loadImage(ICON_IMAGE_PATH_SOUND));
                assert(mSound.loadSound(ITEM_PATH_ROOT + mFileName));
                mSound.stop();
//                mSound.setLoop(OF_LOOP_NONE);
                break;
            case FILE_ITEM_TEXT:
            {
                assert(mIconImage.loadImage(ICON_IMAGE_PATH_TEXT));
                ofFile file(ITEM_PATH_ROOT + mFileName);
                ofBuffer buffer(file);
                while (!buffer.isLastLine())
                {
//                    cout << buffer.getNextLine() << endl;
                    mText.push_back(buffer.getNextLine());
                }
            }
                break;
            case FILE_ITEM_MOVIE:
                assert(mIconImage.loadImage(ICON_IMAGE_PATH_MOVIE));
//                assert(mVideo.loadMovie(ITEM_PATH_ROOT + mFileName));
//                mVideo.stop();
//                mVideo.setLoopState(OF_LOOP_NONE);
                break;
        }
        bPlay = false;
        
        fftSmoothed = new float[8192];
        for (int i = 0; i < 8192; i++){
            fftSmoothed[i] = 0;
        }
        nBandsToGet = 64;
        
        mLineCount = 0;
        
    }
    
    void update()
    {
        switch (mType)
        {
            case FILE_ITEM_SOUND:
            {
                
                float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
                for (int i = 0;i < nBandsToGet; i++){
                    
                    // let the smoothed calue sink to zero:
                    fftSmoothed[i] *= 0.96f;
                    
                    // take the max, either the smoothed or the incoming:
                    if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
                    
                }
            }
                break;
                
            case FILE_ITEM_TEXT:
            {
            }
                break;
                
            case FILE_ITEM_MOVIE:
                break;
        }
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
    
    void play()
    {
        switch (mType)
        {
            case FILE_ITEM_SOUND:
                if(!mSound.getIsPlaying())
                {
                    mSound.play();
                }
                break;
            case FILE_ITEM_TEXT:break;
            case FILE_ITEM_MOVIE: break;
        }
        bPlay = true;
    }
    
    void drawEvent(float width, float height)
    {
        if (!bPlay) return;
        
        switch (mType)
        {
            case FILE_ITEM_SOUND:
            {
                // draw the fft resutls:
                float bitw = width / nBandsToGet;
                for (int i = 0;i < nBandsToGet; i++){
                    ofSetColor(ofColor::fromHsb(ofMap(i, 0, nBandsToGet-1, 0, 255, true), 255, 255));
                    ofRect(i * bitw, height, bitw, -(fftSmoothed[i] * 200));
                }
                if (mSound.getPosition() == 1.0f) mSound.stop();
                if (!mSound.getIsPlaying()) bPlay = false;
            }
                break;
                
            case FILE_ITEM_TEXT:
            {
                if (ofGetFrameNum() % 3 == 0)
                {
                    mLineCount++;
                    if (mLineCount >= mText.size())
                    {
                        mLineCount = 0;
                        bPlay = false;
                    }
                }
                ofDrawBitmapStringHighlight(mText[mLineCount], 10, height*0.5);
                
            }
                break;
                
            case FILE_ITEM_MOVIE:
                break;
        }
    }
};


