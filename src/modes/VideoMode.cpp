//
//  VideoMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "VideoMode.h"

VideoMode::VideoMode(string _name, float _duration) : Mode(_name, _duration) {
    fadeEnter = true;
    fadeExit = true;
    fadeDur = 2.0;
    videoPlayer.loadMovie("vids/sequence5.mov");
    videoPlayer.setVolume(0);
    videoPlayer.setLoopState(OF_LOOP_NORMAL);
}

void VideoMode::start() {
    videoPlayer.play();
}

void VideoMode::update(float hr) {
    videoPlayer.update();
    floorValue = 100*sin(0.1*hr*ofGetElapsedTimef()); //PEND
}


void VideoMode::draw() {
    ofPushStyle();
    ofBackground(255*mult);
    ofSetColor(255);
    videoPlayer.draw(0, 0, width, height);
    ofPopStyle();
}


void VideoMode::reset() {
    videoPlayer.setPosition(0);
}

void VideoMode::preExit() {
    videoPlayer.stop();
}

