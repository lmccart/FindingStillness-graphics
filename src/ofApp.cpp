/*
 64x3 = 192
 32x5 = 160
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    modeManager.setup();
    oscReceiver.setup(3333);
    
//    shaderBlurX.load("shaders/shaderBlurX");
//    shaderBlurY.load("shaders/shaderBlurY");
//    
//    fboBlurOnePass.allocate(width, height);
//    fboBlurTwoPass.allocate(width, height);
//    
    ofEnableAlphaBlending();
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    modeManager.update();

    if (oscReceiver.hasWaitingMessages()) {
        oscMessage.clear();
        oscReceiver.getNextMessage(&oscMessage);
        if (oscMessage.getAddress() == "/start") {
            modeManager.start();
        } else if (oscMessage.getAddress() == "/reset") {
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

//    ofTranslate(0, 32);
//    ofScale(192./1024., 160./768.);
    modeManager.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofLog() << key;
    if (key >= '0' && key <= '9') {
        modeManager.next(key-'0');
    } else if (key == OF_KEY_RETURN) {
        modeManager.next(-1);
    } else if (key == 's') {
        modeManager.start();
    } else if (key == 'r') {
        modeManager.reset();
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}



void ofApp::exit() {
    modeManager.exit();
}
