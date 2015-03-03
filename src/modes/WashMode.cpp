//
//  WashMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/15/15.
//
//

#include "WashMode.h"

WashMode::WashMode(string _name, float _duration, bool _useHR, int _color) : Mode(_name, _duration, _useHR) {
    color = _color;
}


void WashMode::update() {
}


void WashMode::draw() {
    ofPushStyle();
    ofBackground(color);
    ofPopStyle();
    floorValue = 0;
}


void WashMode::reset() {
}

void WashMode::preExit() {
}

