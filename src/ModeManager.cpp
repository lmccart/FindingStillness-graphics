//
//  ModeManager.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "ModeManager.h"
#include "CircleMode.h"


void ModeManager::setup() {
    reset();
    modes.push_back(new CircleMode(5000));
}

void ModeManager::update() {
    float now = ofGetElapsedTimef();
    if (now - modeStartTime >= modes[curMode]->duration) {
        next();
    }
    for (int i=0; i<modes.size(); i++) {
        if (modes[i]->playing) {
            modes[i]->draw();
        }
    }
}

void ModeManager::draw() {
    for (int i=0; i<modes.size(); i++) {
        if (modes[i]->playing) {
            modes[i]->draw();
        }
    }
}

void ModeManager::reset() {
    if (playing) {
        modes[curMode]->exit();
    }
    curMode = 0;
    playing = false;
    modeStartTime = 0;
}

void ModeManager::start() {
    modes[curMode]->enter();
    modeStartTime = ofGetElapsedTimef();
    playing = true;
}

void ModeManager::next() {
    modeStartTime = ofGetElapsedTimef();
    modes[curMode]->exit();
    curMode++;
    if (curMode >= modes.size()) {
        curMode = 0;
    }
    modes[curMode]->enter();
}

