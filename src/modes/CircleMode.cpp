//
//  CircleMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "CircleMode.h"

CircleMode::CircleMode(string _name, float _duration) : Mode(_name, _duration) {
}


void CircleMode::update() {
}


void CircleMode::draw() {
    ofPushStyle();
    ofBackground(black);
    ofSetColor(255);
    ofEllipse(ofGetWidth()/2, ofGetHeight()/2, scale*diameter, scale*diameter);
    ofPopStyle();
}


void CircleMode::reset() {
    diameter = 0;
    scale = 0;
    Tweenzor::add(&scale, 0, 1.0, 0.f, duration, EASE_LINEAR);
    Tweenzor::add(&diameter, 0, ofGetWidth()*1.3, 0.f, 1.f, EASE_IN_OUT_QUAD);
    Tweenzor::getTween(&diameter)->setRepeat( 100, true );
}

void CircleMode::preExit() {
    Tweenzor::removeAllTweens();
}

