#pragma once

#include "common.h"
#include "ofxUI.h"

class MyDesktop : public BaseStage
{
    typedef struct
    {
        ofColor color;
        ofVec3f pos;
        ofVec3f floatPos;
        float radius;
        bool bMouseOver;
        bool bGazeOver;
    } DemoSphere;
    vector<DemoSphere> demos;
    
    
    
public:
    MyDesktop()
    {
        for(int i = 0; i < 20; i++)
        {
            DemoSphere d;
            d.color = ofColor(ofRandom(255),
                              ofRandom(255),
                              ofRandom(255));
            
            d.pos = ofVec3f(ofRandom(-500, 500),0,ofRandom(-500,500));
            
            d.floatPos.x = d.pos.x;
            d.floatPos.z = d.pos.z;
            
            d.radius = ofRandom(2, 50);
            
            d.bMouseOver = false;
            d.bGazeOver  = false;
            
            demos.push_back(d);
        }
    }
    
    string getName(){ return STAGE_00; }
    
    void update()
    {
        for(int i = 0; i < demos.size(); i++){
            demos[i].floatPos.y = ofSignedNoise(ofGetElapsedTimef()/10.0,
                                                demos[i].pos.x/100.0,
                                                demos[i].pos.z/100.0,
                                                demos[i].radius*100.0) * demos[i].radius*20.;
            
        }
    }
    
    void draw()
    {
        ofPushMatrix();
        ofRotate(90, 0, 0, -1);
        ofDrawGridPlane(500.0f, 10.0f, false );
        ofPopMatrix();
        
        ofPushStyle();
        ofNoFill();
        for(int i = 0; i < demos.size(); i++){
            ofPushMatrix();
            //		ofRotate(ofGetElapsedTimef()*(50-demos[i].radius), 0, 1, 0);
            ofTranslate(demos[i].floatPos);
            //		ofRotate(ofGetElapsedTimef()*4*(50-demos[i].radius), 0, 1, 0);
            
            if (demos[i].bMouseOver)
                ofSetColor(ofColor::white.getLerped(ofColor::red, sin(ofGetElapsedTimef()*10.0)*.5+.5));
            else if (demos[i].bGazeOver)
                ofSetColor(ofColor::white.getLerped(ofColor::green, sin(ofGetElapsedTimef()*10.0)*.5+.5));
            else
                ofSetColor(demos[i].color);
            
            ofDrawSphere(demos[i].radius);
            ofPopMatrix();
        }
        
        ofPopStyle();
        
    }
    
};
