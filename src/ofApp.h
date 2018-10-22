#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp, public ofxMidiListener{

	public:
		void setup();
		void update();
		void draw();
        void ___draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
    ofVideoGrabber vid;
    ofVbo vbo;
    ofFbo fbo;
    
    vector<ofFbo> fboStack;
    //int numFrames = 250;
    
    int currentXPosition;
    int currentYPosition;
    
    void newMidiMessage(ofxMidiMessage& message);
    ofxMidiIn midiIn;
    
    ofxPanel panel;
    ofxIntSlider numScans;
    ofxIntSlider numFrames;
    ofxToggle direction;
    
    bool bHide;
};
