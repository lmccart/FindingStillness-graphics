#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    modeManager.setup();
    //server.setup();
    picTaker.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    modeManager.update();
    //server.update();
    //picTaker.update();

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
    } else if (key == 'p') {
        picTaker.takePic();
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
