//
//  Mode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "Mode.h"

Mode::Mode(string _name, float _duration) {
    duration = _duration;
    name = _name;
    
    playing = false;
    black = 0;
    fadeInTime = 1000;
    exitTimer = 0;
    Tweenzor::init();
}

void Mode::enter() {
    ofLog() << "enter " << name << " - " << fadeInTime;
    reset();
    playing = true;
}


void Mode::update() {
    ofLog() << "update";
}

void Mode::draw() {
    ofLog() << "draw";
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