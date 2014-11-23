#pragma once

#include "common.h"
#include "SharedDataReceiver.hpp"
#include "ofxUI.h"

class MyDesktop : public BaseStage
{
    ofImage mDesktopImage;
    ofVboMesh mMesh;

    float extrusionAmount;
    
public:
    MyDesktop()
    {
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
    }
    
    string getName(){ return STAGE_00; }
    
    void update()
    {
        //----------
        // update file items
        //----------
        item_it it = getSharedData().file_items.begin();
        while (it != getSharedData().file_items.end())
        {
            (*it)->update();
            ++it;
        }
        
        //----------
        // update mmd
        //----------
        getSharedData().mmdReceiver.update();
    }
    
    void draw()
    {
        glEnable(GL_DEPTH_TEST);
        
        drawStage(1);
        
        //mMesh.drawVertices();
        
        drawCeilingDisplay();
        
        //----------
        // draw file items
        //----------
        item_it it = getSharedData().file_items.begin();
        while (it != getSharedData().file_items.end())
        {
            (*it)->draw();
            ++it;
        }
        
        glDisable(GL_DEPTH_TEST);
    }
    
    void drawStage(int mode)
    {
        switch (mode) {
            case 0: drawWirePlane(); break;
            case 1: drawImagePlane(); break;
        }
    }
    
    void drawWirePlane()
    {
        ofPushMatrix();
        ofRotate(90, 0, 0, 0);
        ofNoFill();
        ofSetPlaneResolution(30, 30);
        ofDrawPlane(0, 0, DESKTOP_WIDTH*2, DESKTOP_HEIGHT*2);
        ofPopMatrix();
    }
    
    void drawImagePlane()
    {
        ofPushMatrix();
        ofRotate(90, 0, 0, 0);
        ofFill();
        mDesktopImage.draw(-(DESKTOP_WIDTH*0.5), -(DESKTOP_HEIGHT*0.5), DESKTOP_WIDTH * 2, DESKTOP_HEIGHT * 2);
        ofPopMatrix();
    }
    
    void drawCeilingDisplay()
    {
        ofTexture & tex = getSharedData().mmdReceiver.getTextureRef();
        if (!tex.isAllocated()) return;
        
        ofSetColor(255, 255, 255);
        ofPushMatrix();
        ofTranslate(0, 1500, 0);
        ofRotate(90, 0, 0, 0);
        ofFill();
//        ofDrawPlane(0, 0, DESKTOP_WIDTH*2, DESKTOP_HEIGHT*2);
//        ofRect(-(DESKTOP_WIDTH*0.5), -(DESKTOP_HEIGHT*0.5), DESKTOP_WIDTH * 2, DESKTOP_HEIGHT * 2);
        
        tex.draw(-(DESKTOP_WIDTH*0.5), -(DESKTOP_HEIGHT*0.5), DESKTOP_WIDTH * 2, DESKTOP_HEIGHT * 2);
        ofPopMatrix();
    }
};
