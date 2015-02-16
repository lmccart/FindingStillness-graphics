//
//  FaderMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "FaderMode.h"

FaderMode::FaderMode(string _name, float _duration) : Mode(_name, _duration) {
}


void FaderMode::update() {
}


void FaderMode::draw() {
    ofPushStyle();
    int h = 20;
    for (int i=0; i<ofGetHeight(); i+=h) {
        ofSetColor(127+128*sin(0.005*(x-i)));
        ofRect(0, i, ofGetWidth(), h);
    }
    x += diff;
    ofPopStyle();
}


void FaderMode::reset() {
    x = 0;
    Tweenzor::add(&diff, 5, 1.5, 0.f, duration, EASE_LINEAR);
}

void FaderMode::preExit() {
    Tweenzor::removeAllTweens();
}

