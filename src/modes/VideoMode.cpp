//
//  VideoMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "VideoMode.h"

VideoMode::VideoMode(string _name, float _duration, bool _useHR) : Mode(_name, _duration, _useHR) {
    videoPlayer.loadMovie("vids/sequence5.mov");
    videoPlayer.setVolume(0);
    videoPlayer.setLoopState(OF_LOOP_NORMAL);
    fadeMult = 0;
}


void VideoMode::update() {
    videoPlayer.update();
    floorValue = 100*sin(0.1*hr*ofGetElapsedTimef()); //PEND
    if (getModeElapsedTime() < 3.0) {
        fadeMult = getModeElapsedTime()/3.0;
    } else if (getModeElapsedTime() > duration-3.0) {
        fadeMult = (duration - getModeElapsedTime())/3.0;
    }
}


void VideoMode::draw() {
    ofPushStyle();
    ofSetColor(fadeMult*255);
    videoPlayer.draw(0, 0, width, height);
    ofPopStyle();
}


void VideoMode::reset() {
    fadeMult = 0;
    videoPlayer.setPosition(0);
    videoPlayer.play();
}

void VideoMode::preExit() {
    videoPlayer.stop();
}

