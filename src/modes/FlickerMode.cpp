//
//  FlickerMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/15/15.
//
//

#include "FlickerMode.h"

FlickerMode::FlickerMode(string _name, float _duration) : Mode(_name, _duration) {
    fadeEnter = true;
    fadeDur = 3.0;
    holdTime = 5.0;
    val = 0;
    useHr = false;
}


void FlickerMode::update(float hr) {
    if (getModeElapsedTime() > holdTime) {
        baseC = 255*(duration - getModeElapsedTime())/(duration - holdTime);
    }
    val = ofClamp(baseC+55*ofNoise(ofGetFrameNum()*0.05), 0, 255);
    floorValue = val;
}


void FlickerMode::draw() {
    ofPushStyle();
    ofClear(val, 255);
    ofPopStyle();
}


void FlickerMode::reset() {
    baseC = 255;
}

void FlickerMode::preExit() {
}

