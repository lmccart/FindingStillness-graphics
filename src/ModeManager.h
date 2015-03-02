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
    void next(int i);
    void updateHeartrate(float hr);
    void exit();
    
    ofxDmx dmx;
    
private:
    bool playing;
    int curMode;
    float modeStartTime;
    float showStartTime;
    vector<Mode*> modes;
    Mode idleMode;
    float cur_hr;
    float totalDuration;
    float mult;

};
