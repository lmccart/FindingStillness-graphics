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
    
    modes.push_back(new PixelMode("Pixel", 15));
    modes.push_back(new FlockingMode("Flocking", 10));
    modes.push_back(new SeparationMode("Separate", 8, 0));
    modes.push_back(new SeparationMode("Separate", 8, 255));
    modes[modes.size()-1]->fadeExit = true;
    modes.push_back(new VideoMode("Nature", 13));
    modes.push_back(new FaderMode("Fader", 24));
    modes.push_back(new FlickerMode("Flicker", 14));
    
    idleMode = new CircleMode("Circle", 10000);
    
    totalDuration = 0;
    for (int i=0; i<modes.size(); i++) {
        totalDuration += modes[i]->duration;
    }
    
    holdDuration = 180; // secs to wait after person before idle starts
    hold = false;
    
    reset();

}

void ModeManager::update() {
    cur_hr = (incoming_hr+hrRamp)*0.5;
    
    heartRateTime += ((cur_hr / 60.) * 1000.) / ofGetTargetFrameRate();
    heartAmplitude = cos(TWO_PI * (heartRateTime / 1000.));
    heartAmplitude = ofMap(heartAmplitude, -1, +1, 0, 1);

    if (playing) {
        float now = ofGetElapsedTimef();

        if(heartAmplitude > .5 && lastHeartAmplitude <= .5) {
            midi.sendNoteOn(1, 65);
            ofSleepMillis(5);
            midi.sendNoteOff(1, 65);
        }
        lastHeartAmplitude = heartAmplitude;
    
        for (int i=0; i<modes.size(); i++) {
            if (modes[i]->playing) {
                // base value for floorValue, can be overridden by mode
                modes[i]->floorValue = 255 * heartAmplitude;
                modes[i]->update(cur_hr);
            }
        }
        
        float elapsed = modes[curMode]->getModeElapsedTime();
        if (elapsed < 1.5) { // floor fade time
            modes[curMode]->floorValue = lastFloorValue * (1 - elapsed/1.5) + modes[curMode]->floorValue * elapsed/1.5;
        }
        ofLog() << modes[curMode]->floorValue;
        
        if(dmx.isConnected()) {
            int val = modes[curMode]->floorValue;
            for(int chan = 1; chan <= 10; chan++) {
                dmx.setLevel(chan, val);
            }
            dmx.update();
        }
        
        if (now - modeStartTime >= modes[curMode]->duration) {
            next(-1);
        }
        
        
    } else {
        
        if (hold && ofGetElapsedTimef() - modeStartTime > holdDuration) {
            hold = false;
            idleMode->enter();
        }
        if (!hold) idleMode->update(255);
    }
    Tweenzor::update( ofGetElapsedTimeMillis() );
//    ofLog() << mult;
}

void ModeManager::draw() {
    // draw mode
    if (playing) {
        for (int i=0; i<modes.size(); i++) {
            if (modes[i]->playing) {
                modes[i]->drawWithHR(mult, heartAmplitude);
            }
        }

        // draw bg
        ofPushStyle();
        ofSetColor(0);
        ofRect(1024, 0, ofGetWidth()-1024, ofGetHeight());
        
        // draw dmx
        float elapsed = modes[curMode]->getModeElapsedTime();
        if (elapsed < 1.5) { // floor fade time
            modes[curMode]->floorValue = lastFloorValue * (1 - elapsed/1.5) + modes[curMode]->floorValue * elapsed/1.5;
        }
        
        ofLog() << "dmx " << modes[curMode]->floorValue;
        int val = modes[curMode]->floorValue;
        int w = modes[curMode]->width;
        ofSetColor(val, 255);
        ofRect(w+10, 10, ofGetWidth()-20-w, 100);
        ofPopStyle();
        
    } else {
        if (!hold) { // idle
            idleMode->draw();
        } else { // black
            ofClear(0, 255);
        }
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
    showStartTime = 0;
    mult = 1.0;
    hrRamp = 60;
    lastFloorValue = 255;
    
    cur_hr = 60.0;
    incoming_hr = 60.0;
    heartRateTime = 0;
    
    hold = true;
    modeStartTime = ofGetElapsedTimef();
    
    Tweenzor::removeTween(&mult);
    Tweenzor::removeTween(&hrRamp);
    ofLog() << "ModeManager::reset";
    
    midi.sendNoteOn(1, 66);
    ofSleepMillis(30);
    midi.sendNoteOff(1, 66);
}

void ModeManager::start() {
    reset();
    next(0);
    modeStartTime = ofGetElapsedTimef();
    showStartTime = modeStartTime;
    
    Tweenzor::add(&mult, 1.0f, 0.1f, showStartTime+2.0f, showStartTime+5.0f, EASE_LINEAR);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&mult), this, &ModeManager::onCompleteRampDown);
    Tweenzor::add(&hrRamp, 90.0f, 50.0f, showStartTime, showStartTime+totalDuration-20.0, EASE_LINEAR);
    
    midi.sendNoteOn(1, 64);
    ofSleepMillis(30);
    midi.sendNoteOff(1, 64);
    
    playing = true;
    ofLog() << "ModeManager::start";
}

void ModeManager::onCompleteRampDown(float *arg) {
    Tweenzor::add(&mult, 0.1f, 1.0f, 0, totalDuration-25.0, EASE_LINEAR);
}

void ModeManager::end() {
    reset();
    ofLog() << "ModeManager::end";
}
void ModeManager::next(int i) {
    ofLog() << "next";
    modeStartTime = ofGetElapsedTimef();
    
    if (i == -1) { // sequential move to next mode
        lastFloorValue = modes[curMode]->floorValue; // capture last floor for fade
        ofLog() << "last floor value " << lastFloorValue;
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
    modes[curMode]->floorValue = lastFloorValue;
    modes[curMode]->enter();
}

void ModeManager::updateHeartrate(float hr) {
    //cur_hr = hr;
    //ofLog() << "heartrate updated to " << hr;
    
    incoming_hr = hr;
}

void ModeManager::exit() {
    dmx.clear();
    dmx.update(true); // black on shutdown
    midi.closePort();
}