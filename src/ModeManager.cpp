//
//  ModeManager.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "ModeManager.h"


void ModeManager::setup() {
    dmx.connect("tty.usbserial-EN146087", 10);
    dmx.update(true); // black on startup
    
    reset();
    
    Tweenzor::init();
    
    modes.push_back(new PixelMode("Pixel", 15, false));
    modes.push_back(new FlockingMode("Flocking", 10, true));
    modes.push_back(new SeparationMode("Separate", 5, false, 0));
    modes.push_back(new SeparationMode("Separate", 5, false, 255));
    modes.push_back(new VideoMode("Nature", 15, false));
    modes.push_back(new FaderMode("Fader", 30, false));
    modes.push_back(new FlickerMode("Flicker", 10, false));
    modes.push_back(new WashMode("White", 100, false, 100));
    //modes.push_back(new CircleMode("Circle", 30, false));
    
    cur_hr = 0;
    
    modeStartTime = 0;
    showStartTime = 0;
    
    mult = 0;
    
    totalDuration = 0;
    for (int i=0; i<modes.size()-1; i++) {
        totalDuration += modes[i]->duration;
    }
}

void ModeManager::update() {
    if (playing) {
        float now = ofGetElapsedTimef();
        if (now - modeStartTime >= modes[curMode]->duration) {
            next(-1);
        }
    
        float portion = (ofGetElapsedTimef() - showStartTime)/totalDuration;
        if (portion < 0.25) {
            mult = 0.5;
        } else if (portion < 0.5) {
            mult = 0.5 + (portion - 0.25) * 5;
        } else {
            mult = 1.0;
        }
        
        for (int i=0; i<modes.size(); i++) {
            if (modes[i]->playing) {
                modes[i]->update();
            }
        }
        Tweenzor::update( ofGetElapsedTimeMillis() );
        
        if(dmx.isConnected()) {
            int val = modes[curMode]->floorValue;
            for(int chan = 1; chan <= 10; chan++) {
                dmx.setLevel(chan, val);
            }
            dmx.update();
        }
    }
}

void ModeManager::draw() {
    // draw mode
    if (playing) {
        for (int i=0; i<modes.size(); i++) {
            if (modes[i]->playing) {
                modes[i]->drawWithHR(mult);
            }
        }

        // draw bg
        ofPushStyle();
        ofSetColor(0);
        ofRect(1024, 0, ofGetWidth()-1024, ofGetHeight());
        
        // draw dmx
        int val = modes[curMode]->floorValue;
        int w = modes[curMode]->width;
        ofSetColor(val);
        ofRect(w+10, 10, ofGetWidth()-20-w, 100);
        ofPopStyle();
    }
    
}

void ModeManager::reset() {
    if (playing) {
        modes[curMode]->exit();
    }
    curMode = 0;
    playing = false;
    modeStartTime = 0;
    showStartTime = 0;
    mult = 0;
}

void ModeManager::start() {
    reset();
    next(0);
    modeStartTime = ofGetElapsedTimef();
    showStartTime = modeStartTime;
    playing = true;
    ofLog() << "ModeManager::start";
}

void ModeManager::end() {
    reset();
    ofLog() << "ModeManager::end";
}
void ModeManager::next(int i) {
    ofLog() << "next";
    modeStartTime = ofGetElapsedTimef();
    if (playing) modes[curMode]->exit();
    else modes[curMode]->exit();
    if (i == -1) {
        if (curMode == modes.size()-1) {
            end();
        } else {
            curMode++;
        }
    } else {
        if (i >= 0 && i < modes.size()) {
            curMode = i;
        } else ofLog() << "ModeManager::mode out of range";
    }
    modes[curMode]->enter();
}

void ModeManager::updateHeartrate(float hr) {
    cur_hr = hr;
    ofLog() << "heartrate updated to " << hr;
}

void ModeManager::exit() {
    dmx.clear();
    dmx.update(true); // black on shutdown
}