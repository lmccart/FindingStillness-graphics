#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    modeManager.setup();
    oscReceiver.setup(3333);
}

//--------------------------------------------------------------
void ofApp::update(){
    modeManager.update();
    if (oscReceiver.hasWaitingMessages()) {
        oscMessage.clear();
        oscReceiver.getNextMessage(&oscMessage);
        if (oscMessage.getAddress() == "/start") {
            modeManager.start();
        } else if (oscMessage.getAddress() == "/heartrate") {
            modeManager.updateHeartrate(oscMessage.getArgAsFloat(0));
        } else {
            ofLog() << oscMessage.getAddress();
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    modeManager.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofLog() << key;
    if (key >= '0' && key <= '9') {
        modeManager.next(key-'0');
    } else if (key == OF_KEY_RETURN) {
        modeManager.next(-1);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}



//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}
