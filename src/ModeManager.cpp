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
    
    midi.listPorts();
    midi.openPort("IAC Driver Bus 1");
    
    Tweenzor::init();
    

    modes.push_back(new PixelMode("Pixel", 15, false));
    modes.push_back(new FlockingMode("Flocking", 10, false));
    modes.push_back(new SeparationMode("Separate", 8, false, 0));
    modes.push_back(new SeparationMode("Separate", 8, false, 255));
    modes[modes.size()-1]->fadeExit = true;
    modes.push_back(new VideoMode("Nature", 13, false));
    modes.push_back(new FaderMode("Fader", 24, false));
    
    modes.push_back(new FlickerMode("Flicker", 13, false));
    
    
    modes.push_back(new WashMode("White", 30, false, 10));
    
    idleMode = new WashMode("White", 30, false, 40); //new CircleMode("Circle", 10000, false);
    
    cur_hr = 0;
    
    modeStartTime = 0;
    showStartTime = 0;
    
    mult = 0;
    
    totalDuration = 0;
    for (int i=0; i<modes.size()-1; i++) {
        totalDuration += modes[i]->duration;
    }
    
    reset();
    idleMode->enter();

}

void ModeManager::update() {
    if (playing) {
        float now = ofGetElapsedTimef();
        if (now - modeStartTime >= modes[curMode]->duration) {
            next(-1);
        }
    
        float portion = (ofGetElapsedTimef() - showStartTime)/totalDuration;
        if (portion < 0.5) {
            mult = portion + 0.25;
        } else {
            if (mult < 1) {
                mult += 1;
            }
        }
        
        for (int i=0; i<modes.size(); i++) {
            if (modes[i]->playing) {
                modes[i]->update();
            }
        }
        
//        if(dmx.isConnected()) {
//            int val = modes[curMode]->floorValue;
//            for(int chan = 1; chan <= 10; chan++) {
//                dmx.setLevel(chan, val);
//            }
//            dmx.update();
//        }
        
    } else {
        ofLog() << "update " << mult;
        idleMode->update();
    }
    Tweenzor::update( ofGetElapsedTimeMillis() );
}

void ModeManager::draw() {
    // draw mode
    if (playing) {
        for (int i=0; i<modes.size(); i++) {
            if (modes[i]->playing) {
                modes[i]->drawWithHR(1.0);
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
        
    } else {
        idleMode->draw();
    }
    
}

void ModeManager::reset() {
    for (int i=0; i<modes.size(); i++) {
        modes[i]->exit(true);
        modes[i]->reset();
    }
    idleMode->exit(true);
    idleMode->reset();
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
    
    midi.sendNoteOn(1, 64);
    ofSleepMillis(100);
    midi.sendNoteOff(1, 64);
    
    playing = true;
    ofLog() << "ModeManager::start";
}

void ModeManager::end() {
    reset();
    idleMode->enter();
    ofLog() << "ModeManager::end";
}
void ModeManager::next(int i) {
    ofLog() << "next";
    modeStartTime = ofGetElapsedTimef();
    
    if (i == -1) { // sequential move to next mode
        modes[curMode]->exit(false);
        if (curMode == modes.size()-1) {
            end();
        } else {
            curMode++;
        }
    } else { // hard jump to mode
        modes[curMode]->exit(true);
        if (i >= 0 && i < modes.size()) {
            curMode = i;
            modes[curMode]->reset();
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
    midi.closePort();
}