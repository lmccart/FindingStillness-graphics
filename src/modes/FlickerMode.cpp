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
    if (duration - getModeElapsedTime() <= 2.0) {
        float dec = 2*125.0/ofGetFrameRate();
        baseC -= dec;
    }
}


void FlickerMode::draw() {
    ofPushStyle();
    ofBackground(baseC+55*ofNoise(ofGetFrameNum()*0.05));
    ofPopStyle();
}


void FlickerMode::reset() {
    baseC = 200;
}

void FlickerMode::preExit() {
}

