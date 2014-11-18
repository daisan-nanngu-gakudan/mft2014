#pragma once

#include "ofMain.h"
#include "appConst.h"
#include "Bike.h"
#include "Desktop.h"
#include "FinderItem.h"

#include "ofxOsc.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    
        // - - - - app - - - - //

        // Bike and Field
        Bike bike;
        Desktop desktop;
    
        void showDebug();
        void showGuide();
        void setupSpaces();

        // Modes, Flags and so on.
        bool bAnimate;
        bool bFade;
        bool bUseSensor;
        bool bSendMode;
        bool bNeedSending;  // 送信メッセージあり
    
        // Finder Items
        vector<FinderItem> items;
    
        // - - - - oscsend    - - - - //
        ofxOscSender senders[3];

        void setupSender(bool); // bool で起動要否を切替
        void updateSender();
        void send(); // メッセージ送信

        // - - - - oscreceive - - - - //
        ofxOscReceiver receiver;
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
    
        void setupReceiver(bool); // bool で起動要否を切替
        void updateReceiver();

    
private:
        ofBuffer tBuf;
        void setupFinderItems();
        void tBuf2Items();

        // メッセージ送信
        int _sendCount; // メッセージ送信カウンタ
        float _prevSendTime;    // 前回メッセージ送信時刻(ミリ秒);
    
        // メッセージ受信
        string dumpOSC(ofxOscMessage m);
};


namespace Util{
    void crop(ofVec2f* src, const ofVec2f corner1, const ofVec2f corner2);
};