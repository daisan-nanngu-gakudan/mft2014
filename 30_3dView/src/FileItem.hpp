#pragma once

#include "ofMain.h"
#include "common.h"

//enum fileItemType { FILE_ITEM_SOUND, FILE_ITEM_MOVIE, FILE_ITEM_TEXT };

static const string ICON_IMAGE_PATH_SOUND = "images/icon_sound.png";
static const string ICON_IMAGE_PATH_TEXT  = "images/icon_text.png";
static const string ICON_IMAGE_PATH_MOVIE = "images/icon_sound.png"; //TODO: change
static const string ITEM_PATH_ROOT = "items/";



class FileItem
{
protected:
    // common values
    ofVec2f     mPos;
    string      mFileName;
    ofImage     mIconImage;
    bool        bPlay;
    
public:
    // common methods
    virtual void update(){};
    virtual void play(){};
    virtual void drawEvent(float width, float height){};
    
    virtual void draw()
    {
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(mPos.x, 100, mPos.y);
        ofRotate(ofGetElapsedTimef() * 30, 0, 1, 0);
        ofSetRectMode(OF_RECTMODE_CENTER);
        mIconImage.draw(0, 0, 0, 100, -100);
        ofPopMatrix();
        ofPopStyle();
    }
    
    
    // accesser
    const ofVec2f& getPos() const { return mPos; }
    const string& getFileName() const { return mFileName; }
    const ofImage& getIconImage() const { return mIconImage; }
    const bool& isPlay() const { return bPlay; }
};




class SoundFile : public FileItem
{
    ofSoundPlayer mSound;
    int nBandsToGet;
    float * fftSmoothed;
    
public:
    SoundFile(ofVec2f pos, const string & filename)
    {
        mPos.set(pos);
        mFileName = filename;
        
        assert(mIconImage.loadImage(ICON_IMAGE_PATH_SOUND));
        assert(mSound.loadSound(ITEM_PATH_ROOT + mFileName));
        mSound.stop();
        // mSound.setLoop(OF_LOOP_NONE);
        
        fftSmoothed = new float[8192];
        for (int i = 0; i < 8192; i++){
            fftSmoothed[i] = 0;
        }
        nBandsToGet = 64;
        bPlay = false;
    }
    
    void update()
    {
        float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
        for (int i = 0;i < nBandsToGet; i++){
            
            // let the smoothed calue sink to zero:
            fftSmoothed[i] *= 0.96f;
            
            // take the max, either the smoothed or the incoming:
            if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
            
        }
    }
    
    void play()
    {
        if(!mSound.getIsPlaying())
        {
            mSound.play();
        }
        bPlay = true;
    }
    
    void drawEvent(float width, float height)
    {
        if (!bPlay) return;
        
        // draw the fft resutls:
        float bitw = width / nBandsToGet;
        for (int i = 0;i < nBandsToGet; i++)
        {
            ofSetColor(ofColor::fromHsb(ofMap(i, 0, nBandsToGet-1, 0, 255, true), 255, 255));
            ofRect(i * bitw, height, bitw, -(fftSmoothed[i] * 200));
        }
        if (mSound.getPosition() == 1.0f) mSound.stop();
        if (!mSound.getIsPlaying()) bPlay = false;
    }
};




class TextFile : public FileItem
{
    vector<string> mText;
    int mLineCount;
    
public:
    TextFile(ofVec2f pos, const string & filename)
    {
        mPos.set(pos);
        mFileName = filename;
        
        assert(mIconImage.loadImage(ICON_IMAGE_PATH_TEXT));
        ofFile file(ITEM_PATH_ROOT + mFileName);
        ofBuffer buffer(file);
        while (!buffer.isLastLine())
        {
            mText.push_back(buffer.getNextLine());
        }
        bPlay = false;
        
        mLineCount = 0;
    }
    
    void update()
    {
        
    }
    
    void play()
    {
        bPlay = true;
    }
    
    void drawEvent(float width, float height)
    {
        if (!bPlay) return;
        
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
};




class Folder : public FileItem
{
public:
    Folder(ofVec2f pos, const string & filename)
    {
        mPos.set(pos);
        mFileName = filename;
    }
    
    void update()
    {
        
    }
    
    void draw()
    {
        
    }
    
    void play()
    {
        
    }
    
    void drawEvent(float width, float height)
    {
        
    }
};

