//
//  SwipeMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "SwipeMode.h"

SwipeMode::SwipeMode(string _name, float _duration) : Mode(_name, _duration) {
    Tweenzor::init();
    reset();
}

void SwipeMode::onComplete(float* arg) {
    reset();
}

void SwipeMode::update() {
    Tweenzor::update( ofGetElapsedTimeMillis() );
}


void SwipeMode::draw() {
    ofPushStyle();
    ofBackground(black);
    ofSetColor(255);
    ofRect(x, 0, ofGetWidth(), ofGetHeight());
    ofRect(0, y, ofGetWidth(), ofGetHeight());
    ofPopStyle();
}


void SwipeMode::reset() {
    x = -ofGetWidth();
    y = -ofGetHeight();
    Tweenzor::removeAllTweens();
    Tweenzor::add(&x, -ofGetWidth(), 0, 0.f, 1.f, EASE_IN_EXPO);
    Tweenzor::add(&y, -ofGetHeight(), 0, 2.f, 1.f, EASE_IN_EXPO);
    Tweenzor::getTween(&x)->setRepeat( 1, true );
    Tweenzor::getTween(&y)->setRepeat( 1, true );
    Tweenzor::addCompleteListener( Tweenzor::getTween(&y), this, &SwipeMode::onComplete);
}

void SwipeMode::preExit() {
    Tweenzor::pauseAllTweens();
}

