//
//  CircleMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "CircleMode.h"

CircleMode::CircleMode(string _name, float _duration) : Mode(_name, _duration) {
    Tweenzor::init();
}


void CircleMode::update() {
    scale+=0.001;
    Tweenzor::update( ofGetElapsedTimeMillis() );
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
    Tweenzor::add(&diameter, 0, ofGetWidth(), 0.f, 1.f, EASE_IN_OUT_QUAD);
    Tweenzor::getTween(&diameter)->setRepeat( 100, true );
}

void CircleMode::preExit() {
    Tweenzor::pauseAllTweens();
}

