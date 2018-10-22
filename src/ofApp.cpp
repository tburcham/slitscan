#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    vid.setup(ofGetWidth(), ofGetHeight());
    fbo.allocate(vid.getWidth(), vid.getHeight(), GL_RGBA);
    
    ofLog() << "GL Version" << glGetString( GL_VERSION );
    
    midiIn.listInPorts();
    /*midiIn.openPort(0);
    midiIn.addListener(this);*/
    
    ofLog() << "Video Initialized" << endl;
    ofLog() << "Midi Initialized" << endl;
    
    panel.setup("", "settings.xml", 10, 10);
    
    panel.add(numScans.setup("num scans", 20, 1, 200));
    panel.add(numFrames.setup("num frames", 150, 50, 300));
    panel.add(direction.setup("direction"));
    panel.loadFromFile("settings.xml");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    vid.update();
    
    cout << direction << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    
    ofFbo f;
    f.allocate(vid.getWidth(), vid.getHeight(), GL_RGBA);
    //f.clear();
    
    f.begin();
    
    ofClear(255,255,255, 0);
    ofTexture t = vid.getTexture();
    t.draw(0, 0);
    
    f.end();
    
    fboStack.push_back(f);
    
    if (fboStack.size() > numFrames){
        fboStack.erase(fboStack.begin());
    }
    
    
    
    
    
    //fbo.clear();
    fbo.begin();
    ofClear(255,255,255, 0);
    
    //cout << "Stack Size:" << fboStack.size() << endl;
    
    int scanWidth;
    if (direction) {
        scanWidth = ofGetWidth() / numScans;
    } else {
        scanWidth = ofGetHeight() / numScans;
    }
    
    for (int i = 0; i < fboStack.size(); i++) {
        
        //cout << "i:" << i << fboStack[i].isAllocated() << endl;
        
        //if (fboStack[i].isAllocated()) {
            ofTexture t = fboStack[fboStack.size() - i - 1].getTexture();
        
        
            if (direction) {
                t.drawSubsection(scanWidth * i, 0, scanWidth, ofGetHeight(), scanWidth * i, 0, scanWidth, ofGetHeight());
            } else {
                t.drawSubsection(0, scanWidth * i, ofGetWidth(), scanWidth, 0, scanWidth * i, ofGetWidth(), scanWidth);
            }
        //}
        
    }
    
    fbo.end();
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    if (!bHide) {
        panel.draw();
        // ofDisableDepthTest();
    } else {
        //ofEnableDepthTest();
    }
}

//--------------------------------------------------------------
void ofApp::___draw(){
    
    ofBackground(0);
    
    fbo.begin();

    ofTexture t = vid.getTexture();
    
    int scanWidth = numScans / ofGetHeight();
    
    if (direction) {
        t.drawSubsection(currentXPosition, 0, scanWidth, ofGetHeight(), currentXPosition, 0, scanWidth, ofGetHeight());
    } else {
        t.drawSubsection(0, currentYPosition, ofGetWidth(), scanWidth, 0, currentYPosition, ofGetWidth(), scanWidth);
    }
    
    fbo.end();
    
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    currentXPosition += scanWidth;
    if (currentXPosition > vid.getWidth()) {
        currentXPosition = 0;
    }
    currentYPosition += scanWidth;
    if (currentYPosition > vid.getHeight()) {
        currentYPosition = 0;
    }
    
    if (!bHide) {
        panel.draw();
        // ofDisableDepthTest();
    } else {
        //ofEnableDepthTest();
    }
}


//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& message) {
    
    switch(message.control) {
        case 21:
            numScans = ofMap(message.value, 0, 127, numScans.getMin(), numScans.getMax());
            break;
        /*case 22:
            depth = ofMap(message.value, 0, 127, depth.getMin(), depth.getMax());
            break;
        case 23:
            spacing = ofMap(message.value, 0, 127, spacing.getMin(), spacing.getMax());
            break;
        case 24:
            width = ofMap(message.value, 0, 127, width.getMin(), width.getMax());
            break;*/
            //        case 25:
            //            speed = ofMap(message.value, 0, 127, speed.getMin(), speed.getMax());
            //            break;
            //        case 26:
            //            numShapes = ofMap(message.value, 0, 127, numShapes.getMin(), numShapes.getMax());
            //            break;
        default:
            cout << message.control << " not assigned" << endl;
            
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'h'){
        bHide = !bHide;
    }
    if (key == 's') {
        ofSaveScreen("out" + ofGetTimestampString() + ".png");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
