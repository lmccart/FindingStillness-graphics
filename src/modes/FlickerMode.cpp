//
//  FlickerMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/15/15.
//
//

#include "FlickerMode.h"

FlickerMode::FlickerMode(string _name, float _duration, bool _useHR) : Mode(_name, _duration, _useHR) {
}


void FlickerMode::update() {
    baseC = 200*(duration - getModeElapsedTime())/duration;
}


void FlickerMode::draw() {
    ofPushStyle();
    ofBackground(MAX(0, baseC+55*ofNoise(ofGetFrameNum()*0.05)));
    ofPopStyle();
}


void FlickerMode::reset() {
    baseC = 200;
}

void FlickerMode::preExit() {
}

