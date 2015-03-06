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
    pulseFbo.allocate(width, height);
    hr = 60;
    targetHR = 60;
    floorValue = 100;
    width = 1024;
    height = 768;
    fadeEnter = false;
    fadeExit = false;
    fadeDur = 2.0;
    
    enterMult = 1;
    exitMult = 1;
    
    Tweenzor::init();
}

void Mode::enter() {
    if (fadeEnter) {
        enterMult = 0;
        exitMult = 1;
    }
    
    ofLog() << "enter " << name;
    startTime = ofGetElapsedTimef();
    enterMult = 1.0;
    exitMult = 1.0;
    reset();
    playing = true;
}


void Mode::update() {
}

void Mode::draw() {
    //ofLog() << "draw";
}

void Mode::drawWithHR(float _mult) {
    
    if (fadeEnter && getModeElapsedTime() < fadeDur) {
        enterMult = getModeElapsedTime()/fadeDur;
    } else if (fadeExit && getModeElapsedTime() - duration < fadeDur) {
        exitMult = 1 - ((getModeElapsedTime() - duration) / fadeDur);
    } else if (fadeExit &&  getModeElapsedTime() - duration >= fadeDur) {
        exit();
    }
    
    mult = _mult;
    pulseFbo.begin();
        ofClear(0, 0, 0);
        draw();
    pulseFbo.end();
    float alpha = useHR ? 170+85*sin(0.001*hr*ofGetFrameNum()) : 255;
    ofPushStyle();
    ofSetColor(alpha*mult*enterMult*exitMult);
    ofLog() << name <<" " << alpha*mult*enterMult*exitMult;
    pulseFbo.draw(0, 0);
    ofPopStyle();
}

float Mode::getModeElapsedTime() {
    return ofGetElapsedTimef() - startTime;
}

void Mode::updateHR(float _hr) {
    targetHR = ofClamp(ofMap(_hr, 0, 100, 0, 255), 0, 255);
}

void Mode::preExit() {
    ofLog() << "preExit";
}

void Mode::reset() {
    ofLog() << "reset";
}

void Mode::exit() {
    if (fadeExit) {
        enterMult = 1.0;
        exitMult = 0;
    } else {
        ofLog() << "exit " << name;
        playing = false;
        preExit();
    }
}