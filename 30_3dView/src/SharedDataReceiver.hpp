#pragma once

#include "ofMain.h"
#include "ofxSharedMemory.h"

namespace mmd
{
    bool isServer = false;
    int videoWidth = 640;
    int videoHeight = 480;
    int memorySize = videoWidth * videoHeight * 3;
    string memoryKey = "camera";
}


class SharedDataReceiver
{
    // when creating an ofxSharedMemory, use the <> to assign a data type
    ofxSharedMemory<unsigned char*> memoryMappedFile;
    
    bool isConnected;
    ofTexture texture; // created from memory mapped file
    
public:
    
    SharedDataReceiver()
    {
        texture.allocate(mmd::videoWidth, mmd::videoHeight, GL_RGB);
        
        // setup + connect
        memoryMappedFile.setup(mmd::memoryKey, mmd::memorySize, mmd::isServer);
        isConnected = memoryMappedFile.connect();
        
        ofLog() << "Memory was mapped? " << isConnected;
        ofLog() << "Memory key: " << mmd::memoryKey;
        ofLog() << "Memory size: " << mmd::memorySize;
    }
    
    void update()
    {
        ofSetWindowTitle( ofToString(mmd::isServer ? "Server connected: " : "Client connected: ") + ofToString(isConnected ? "YES" : "NO") + ", FPS: " + ofToString(ofGetFrameRate()));
        
        // if not connected, try reconnect every 5 seconds or so
        if(!isConnected && ofGetFrameNum() % 300 == 0) {
            isConnected = memoryMappedFile.connect();
        }
        
        if(isConnected) {
            texture.loadData(memoryMappedFile.getData(), mmd::videoWidth, mmd::videoHeight, GL_RGB);
        }
        
    }
    
    void draw()
    {
        // server is blue, client is yellow
        (mmd::isServer) ? ofBackground(0, 255, 255) : ofBackground(255, 255, 0);
        
        ofSetColor(255);
        texture.draw(0,0);
        ofSetColor(0);
    }
    
    ofTexture & getTextureRef() { return texture; }
    
};