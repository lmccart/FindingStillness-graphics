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
    Mode(string _name, float _duration);
    void enter();
    virtual void start();
    virtual void update(float hr);
    virtual void draw();
    void drawWithHR(float _mult, float _ha);
    virtual void preExit();
    virtual void reset();
    void exit(bool hard);
    float getModeElapsedTime();
    
    bool playing;
    float duration;
    float black;
    string name;
    float startTime;
    float floorValue;
    float width, height;
    float mult;
    float enterMult, exitMult;
    bool fadeEnter, fadeExit;
    float fadeDur;
    
private:
    ofFbo pulseFbo;
};


