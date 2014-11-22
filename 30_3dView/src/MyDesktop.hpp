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
    
    ofImage mDesktopImage;
    ofVboMesh mMesh;
    
    float extrusionAmount;
    
public:
    MyDesktop()
    {
        for(int i = 0; i < 20; i++)
        {
            DemoSphere d;
            d.color = ofColor(ofRandom(255),
                              ofRandom(255),
                              ofRandom(255));
            
            d.pos = ofVec3f(ofRandom(-(DESKTOP_WIDTH*0.5), DESKTOP_WIDTH*0.5),0,ofRandom(-(DESKTOP_HEIGHT*0.5), DESKTOP_HEIGHT*0.5));
            
            d.floatPos.x = d.pos.x;
            d.floatPos.z = d.pos.z;
            
            d.radius = ofRandom(2, 50);
            
            d.bMouseOver = false;
            d.bGazeOver  = false;
            
            demos.push_back(d);
        }
        
        VALIDE(mDesktopImage.loadImage(DESKTOP_IMAGE_PATH));
        
        float pixWidth = mDesktopImage.getWidth();
        float pixHeight = mDesktopImage.getHeight();
        float interval = 20;
        for (int y = 0; y < pixHeight; y += interval)
        {
            for (int x = 0; x< pixWidth; x += interval)
            {
                mMesh.addVertex(ofPoint(x, 0, y));
                mMesh.addColor(mDesktopImage.getColor(x, y));
            }
        }
        extrusionAmount = 30.0 * FIELD_AMPLIFY / 3;
        
        //
        // i don't understand yet.
        //
        for (int y = 0; y< pixHeight-1; y += interval)
        {
            for (int x=0; x< pixWidth-1; x += interval)
            {
                mMesh.addIndex(x+y* pixWidth);				// 0
                mMesh.addIndex((x+1)+y* pixWidth);			// 1
                mMesh.addIndex(x+(y+1)* pixWidth);			// 10
                
                mMesh.addIndex((x+1)+y* pixWidth);			// 1
                mMesh.addIndex((x+1)+(y+1)* pixWidth);		// 11
                mMesh.addIndex(x+(y+1)* pixWidth);			// 10
            }
        }
        
//        unsigned char * pix = mDesktopImage.getPixels();
//        for (int i=0; i< pixWidth * pixHeight; i += )
//        {
//            ofFloatColor sampleColor(pix[i*3]/255.f,				// r
//                                     pix[i*3+1]/255.f,			// g
//                                     pix[i*3+2]/255.f);			// b
//            
//            //now we get the vertex aat this position
//            //we extrude the mesh based on it's brightness
//            ofVec3f tmpVec = mMesh.getVertex(i);
//            
//            // update koudo ?altitude? popup height
//            tmpVec.z = sampleColor.getBrightness() * extrusionAmount;
//            mMesh.setVertex(i, tmpVec);
//            
//            mMesh.setColor(i, sampleColor);
//        }
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
        ofRotate(90, 0, 0, 0);
        ofNoFill();
        ofSetPlaneResolution(50, 50);
        ofDrawPlane(0, 0, DESKTOP_WIDTH, DESKTOP_HEIGHT);
        ofPopMatrix();
        
        ofPushStyle();
        ofNoFill();
        for(int i = 0; i < demos.size(); i++)
        {
            ofPushMatrix();
            ofTranslate(demos[i].floatPos);
            
            if (demos[i].bMouseOver)
                ofSetColor(ofColor::white.getLerped(ofColor::red, sin(ofGetElapsedTimef()*10.0)*.5+.5));
            else if (demos[i].bGazeOver)
                ofSetColor(ofColor::white.getLerped(ofColor::green, sin(ofGetElapsedTimef()*10.0)*.5+.5));
            else
                ofSetColor(demos[i].color);
            
            ofDrawSphere(demos[i].radius);
            ofPopMatrix();
        }
        
        mMesh.drawVertices();
        
        ofPopStyle();
        
    }
    
//    void updateMesh()
//    {
//        float pixWidth = mDesktopImage.getWidth();
//        float pixHeight = mDesktopImage.getHeight();
//        unsigned char * pix = mDesktopImage.getPixels();
//        
//        for (int i=0; i< pixWidth * pixHeight; i += )
//        {
//            ofFloatColor sampleColor(pix[i*3]/255.f,				// r
//                                     pix[i*3+1]/255.f,			// g
//                                     pix[i*3+2]/255.f);			// b
//            
//            //now we get the vertex aat this position
//            //we extrude the mesh based on it's brightness
//            ofVec3f tmpVec = mMesh.getVertex(i);
//            
//            // update koudo ?altitude? popup height
//            tmpVec.z = sampleColor.getBrightness() * extrusionAmount;
//            mMesh.setVertex(i, tmpVec);
//            
//            mMesh.setColor(i, sampleColor);
//        }
//    }
};
