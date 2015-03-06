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
    
    Tweenzor::init();
}

void Mode::enter() {
    ofLog() << "enter " << name;
    startTime = ofGetElapsedTimef();
    reset();
    playing = true;
}


void Mode::update() {
    //ofLog() << "update";
    hr = (targetHR - hr)*0.5 + hr;
}

void Mode::draw() {
    //ofLog() << "draw";
}

void Mode::drawWithHR(float _mult) {
    mult = _mult;
    pulseFbo.begin();
        ofClear(0, 0, 0);
        draw();
    pulseFbo.end();
    float alpha = useHR ? 170+85*sin(0.001*hr*ofGetFrameNum()) : 255;
    ofPushStyle();
    ofSetColor(alpha*mult);
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
    playing = false;
    preExit();
}

