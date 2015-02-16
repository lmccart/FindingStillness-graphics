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
}


void WashMode::update() {
}


void WashMode::draw() {
    ofPushStyle();
    ofBackground(color);
    ofPopStyle();
}


void WashMode::reset() {
}

void WashMode::preExit() {
}

