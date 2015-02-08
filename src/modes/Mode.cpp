//
//  Mode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "Mode.h"

Mode::Mode(float duration) {
    duration = duration;
    
    playing = false;
    black = 0;
    fadeInTime = 1000;
}

void Mode::enter() {
    ofLog() << "enter";
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
    preExit();
}