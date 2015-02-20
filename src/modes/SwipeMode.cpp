//
//  SwipeMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "SwipeMode.h"

SwipeMode::SwipeMode(string _name, float _duration, bool _useHR) : Mode(_name, _duration, _useHR) {
}


void SwipeMode::update() {
    y+= dir*ofGetHeight()/(0.5*duration*ofGetFrameRate());
    if (y >= ofGetHeight()) {
        y = ofGetHeight();
        dir = -1;
    }
}


void SwipeMode::draw() {
    ofPushStyle();
    ofSetColor(255);
    ofRect(0, y, ofGetWidth(), 2*ofGetHeight());
    ofPopStyle();
}


void SwipeMode::reset() {
    y = 0;
    dir = 1;
    
}

void SwipeMode::preExit() {
}

