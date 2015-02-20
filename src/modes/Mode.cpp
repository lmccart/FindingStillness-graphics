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
    exitTimer = 1;
    enterTimer = 0;
    fadeDur = 1.5;
    pulseFbo.allocate(ofGetWidth(), ofGetHeight());
    hr = 60;
    targetHR = 60;
    Tweenzor::init();
}

void Mode::enter() {
    ofLog() << "enter " << name;
    exitTimer = 1;
    enterTimer = 0;
    Tweenzor::add(&enterTimer, 0, 1, 0.f, fadeDur, EASE_LINEAR);
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
    pulseFbo.begin();
        ofClear(0, 0, 0);
        draw();
    pulseFbo.end();
    float alpha = useHR ? 170+85*sin(0.001*hr*ofGetFrameNum()) : 255;
    ofSetColor(255, alpha*exitTimer*enterTimer);
    pulseFbo.draw(0, 0);
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
    Tweenzor::add(&exitTimer, 1, 0, 0.f, fadeDur, EASE_LINEAR);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&exitTimer), this, &Mode::exitComplete);
}

void Mode::exitComplete(float *arg) {
    preExit();
    playing = false;
}