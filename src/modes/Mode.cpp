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
    width = 1024;
    height = 768;
    pulseFbo.allocate(width, height);
    floorValue = 100;
    fadeEnter = false;
    fadeExit = false;
    fadeDur = 1.5;
    
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
    start();
    playing = true;
}

void Mode::start() {
    ofLog() << "start";
}

void Mode::update(float hr) {
}

void Mode::draw() {
    //ofLog() << "draw";
}

void Mode::drawWithHR(float _mult, float _hr) {
    
    if (fadeEnter && getModeElapsedTime() < fadeDur) {
        enterMult = getModeElapsedTime()/fadeDur;
    } else if (fadeExit && getModeElapsedTime() - duration < fadeDur && getModeElapsedTime() - duration >= 0) {
        exitMult = MAX(0, 1 - ((getModeElapsedTime() - duration) / fadeDur));
    } else if (fadeExit && getModeElapsedTime() - duration >= fadeDur) {
        playing = false;
        preExit();
    }
    
    mult = _mult;
    pulseFbo.begin();
        ofPushStyle();
        ofClear(0);
        draw();
        ofPopStyle();
    pulseFbo.end();
    
    float alpha =  200+55*sin(0.001*_hr*ofGetFrameNum()); // PEND KYLE
    
    ofPushStyle();
    ofSetColor(255, alpha*mult*enterMult*exitMult);
    //ofLog() << name <<" " << alpha*mult*enterMult*exitMult << " " << mult << " " << exitMult;
    pulseFbo.draw(0, 0);
    ofPopStyle();
}

float Mode::getModeElapsedTime() {
    return ofGetElapsedTimef() - startTime;
}

void Mode::preExit() {
    ofLog() << "preExit";
}

void Mode::reset() {
    ofLog() << "reset";
}

void Mode::exit(bool hard) {
    if (!hard && fadeExit) {
        enterMult = 1.0;
        exitMult = 1.0;
    } else {
        ofLog() << "exit " << name;
        playing = false;
        preExit();
    }
}