//
//  VideoMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "VideoMode.h"

VideoMode::VideoMode(string _name, float _duration) : Mode(_name, _duration) {
    videoPlayer.loadMovie("vids/sequence2.mov");
    videoPlayer.setVolume(0);
    videoPlayer.setLoopState(OF_LOOP_NORMAL);
}


void VideoMode::update() {
    videoPlayer.update();
}


void VideoMode::draw() {
    ofPushStyle();
    videoPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
}


void VideoMode::reset() {
    videoPlayer.setPosition(0);
    videoPlayer.play();
}

void VideoMode::preExit() {
    videoPlayer.stop();
}

