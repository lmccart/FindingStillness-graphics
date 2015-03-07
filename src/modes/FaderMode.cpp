//
//  FaderMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "FaderMode.h"

FaderMode::FaderMode(string _name, float _duration, bool _useHR) : Mode(_name, _duration, _useHR) {
    fadeEnter = true;
    fadeExit = true;
    fadeDur = 3.0;
}

void FaderMode::start() {
    Tweenzor::add(&strength, 0.5f, 3.0f, 0.0f, (float)0.5*duration, EASE_LINEAR);
    Tweenzor::getTween(&strength)->setRepeat(1, true);
    Tweenzor::add(&diff, 4, 1, 0.25*duration, duration, EASE_LINEAR);
}

void FaderMode::update() {
    floorValue = 255*sin(0.1*hr*ofGetElapsedTimef()); //PEND
}


void FaderMode::draw() {
    
    ofPushStyle();
    float h = 5;
    for (int i=0; i<width; i+=h) {
        float c = 127+128*ofClamp(strength*cos(d*(x-i)), -1, 1);
        if (getModeElapsedTime() < 1.0) {
            c = ofMap(c, 0, 255, 255*(1.01-getModeElapsedTime()), 255);
        }
        ofSetColor(ofClamp(c, 0, 255));
        ofRect(0, i, width, h);
    }
    x -= diff;
    ofPopStyle();
}


void FaderMode::reset() {
    x = 0;
    d = 0.005;
    diff = 4;
    strength = 0.5;
}

void FaderMode::preExit() {
    Tweenzor::removeTween(&strength);
    Tweenzor::removeTween(&diff);
}

