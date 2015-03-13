//
//  SwipeMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "SwipeMode.h"

SwipeMode::SwipeMode(string _name, float _duration) : Mode(_name, _duration) {
}


void SwipeMode::update() {
    y+= dir*height/(0.5*duration*ofGetFrameRate());
    if (y >= height) {
        y = height;
        dir = -1;
    }
}


void SwipeMode::draw() {
    ofPushStyle();
    ofSetColor(255);
    ofRect(0, y, width, 2*height);
    ofPopStyle();
}


void SwipeMode::reset() {
    y = 0;
    dir = 1;
    
}

void SwipeMode::preExit() {
}

