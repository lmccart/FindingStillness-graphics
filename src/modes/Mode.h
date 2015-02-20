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
    void drawWithHR();
    void updateHR(float _hr);
    virtual void preExit();
    virtual void reset();
    void exit();
    void slowExit();
    void exitComplete(float *arg);
    
    bool playing;
    float duration;
    float black;
    string name;
    float hr;
    bool useHR;

    
private:
    float exitTimer;
    float enterTimer;
    float fadeDur;
    ofFbo pulseFbo;
    float targetHR;
};


