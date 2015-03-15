//
//  WashMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/15/15.
//
//

#include "WashMode.h"

WashMode::WashMode(string _name, float _duration, int _color) : Mode(_name, _duration) {
    color = _color;
    useHr = false;
}


void WashMode::update(float hr) {
    floorValue = 0;
}


void WashMode::draw() {
    ofPushStyle();
    ofClear(color, 255);
    ofPopStyle();
}


void WashMode::reset() {
}

void WashMode::preExit() {
}

