//
//  Mode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "Mode.h"

Mode::Mode(string _name, float _duration, bool _useHR) {
    duration = _duration;
    name = _name;
    useHR = _useHR;
    
    playing = false;
    black = 0;
    fadeInTime = 1000;
    exitTimer = 0;
    pulseFbo.allocate(ofGetWidth(), ofGetHeight());
    hr = 60;
    targetHR = 60;
    Tweenzor::init();
}

void Mode::enter() {
    ofLog() << "enter " << name << " - " << fadeInTime;
    reset();
    playing = true;
}


void Mode::update() {
    ofLog() << "update";
    hr = (targetHR - hr)*0.5 + hr;
}

void Mode::draw() {
    ofLog() << "draw";
}

void Mode::drawWithHR() {
    if (useHR) {
        pulseFbo.begin();
            ofClear(0, 0, 0);
            draw();
        pulseFbo.end();
        ofSetColor(255, 170+85*sin(0.001*hr*ofGetFrameNum()));
        pulseFbo.draw(0, 0);
    } else {
        draw();
    }
}

void Mode::updateHR(float _hr) {
    targetHR = ofClamp(ofMap(_hr, 0, 80, 0, 255), 0, 255);
}

void Mode::preExit() {
    ofLog() << "preExit";
}

void Mode::reset() {
    ofLog() << "reset";
}


void Mode::exit() {
    playing = false;
    preExit();
}

void Mode::slowExit() {
    ofLog() << "exit " << name;
    preExit();
    Tweenzor::add(&exitTimer, 0, 1, 0.f, 1.0f, EASE_LINEAR);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&exitTimer), this, &Mode::exitComplete);
}

void Mode::exitComplete(float *arg) {
    playing = false;
}