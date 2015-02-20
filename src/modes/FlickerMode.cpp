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
}


void FlickerMode::draw() {
    ofPushStyle();
    ofBackground(255);
    float r = ofRandom(1.0);
    if (r < 0.03) {
        ofBackground(150);
    }
    ofPopStyle();
}


void FlickerMode::reset() {
}

void FlickerMode::preExit() {
}

