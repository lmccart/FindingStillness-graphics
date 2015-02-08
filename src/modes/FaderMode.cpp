//
//  FaderMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "FaderMode.h"

FaderMode::FaderMode(string _name, float _duration) : Mode(_name, _duration) {
    reset();
}


void FaderMode::update() {
}


void FaderMode::draw() {
    ofPushStyle();
    ofBackground(black);
    int h = 20;
    for (int i=0; i<ofGetHeight(); i+=h) {
        ofSetColor(127+128*sin(0.005*(x-i)));
        ofRect(0, i, ofGetWidth(), h);
    }
    x += h;
    ofPopStyle();
}


void FaderMode::reset() {
    x = 0;
}

void FaderMode::preExit() {
}

