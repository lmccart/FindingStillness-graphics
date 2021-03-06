//
//  ModeManager.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxDmx.h"
#include "ofxMidi.h"
#include "CircleMode.h"
#include "FaderMode.h"
#include "VideoMode.h"
#include "SeparationMode.h"
#include "FlockingMode.h"
#include "SwipeMode.h"
#include "PixelMode.h"
#include "FlickerMode.h"
#include "WashMode.h"

class ModeManager {
    
public:
    void setup();
    void update();
    void draw();
    void reset();
    void start();
    void end();
    void next(int i);
    void updateHeartrate(float hr);
    void exit();
    void onCompleteRampDown(float* arg);
    
    ofxDmx dmx;
    ofxMidiOut midi;
    
    float modeStartTime;
    bool hold;
    
private:
    bool playing;
    int curMode;
    float showStartTime;
    vector<Mode*> modes;
    Mode *idleMode;
    float cur_hr;
    float incoming_hr;
    float totalDuration;
    float mult;
    float hrRamp;
    float holdDuration;
    unsigned long heartRateTime;
    float heartAmplitude, lastHeartAmplitude;
    float lastFloorValue;

};
