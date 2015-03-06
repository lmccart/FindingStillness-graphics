//
//  Mode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxTweenzor.h"

class Mode {
    
public:
    Mode(string _name, float _duration, bool _useHR);
    virtual void enter();
    virtual void update();
    virtual void draw();
    void drawWithHR(float _mult);
    void updateHR(float _hr);
    virtual void preExit();
    virtual void reset();
    void exit();
    float getModeElapsedTime();
    
    bool playing;
    float duration;
    float black;
    string name;
    float hr;
    bool useHR;
    float startTime;
    float floorValue;
    float width, height;
    float mult;
    float enterMult, exitMult;
    bool fadeEnter, fadeExit;
    float fadeDur;
    
private:
    ofFbo pulseFbo;
    float targetHR;
};


