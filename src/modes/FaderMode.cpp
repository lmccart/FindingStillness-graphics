//
//  FaderMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "FaderMode.h"

FaderMode::FaderMode(string _name, float _duration, bool _useHR) : Mode(_name, _duration, _useHR) {
}


void FaderMode::update() {
}


void FaderMode::draw() {
    ofPushStyle();
    float h = 5;
    for (int i=0; i<ofGetWidth(); i+=h) {
        ofSetColor(127+128*sin(d*(x-i)));
        ofRect(i, 0, h, ofGetHeight());
    }
    x += diff;
    ofPopStyle();
}


void FaderMode::reset() {
    x = 0;
    d = 0.005;
    Tweenzor::add(&diff, 4, 1.5, 0.f, duration, EASE_LINEAR);
    Tweenzor::add(&d, 0.01, 0.001, 0.f, duration, EASE_LINEAR);
}

void FaderMode::preExit() {
    Tweenzor::removeTween(&diff);
    Tweenzor::removeTween(&d);
}

