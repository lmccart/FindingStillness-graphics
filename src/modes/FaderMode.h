//
//  FaderMode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//
#pragma once

#include "ofMain.h"
#include "Mode.h"

class FaderMode : public Mode {
    
public:
    FaderMode(string _name, float _duration, bool _useHR);
    void update();
    void draw();
    void reset();
    void preExit();
    
    
private:
    float x;
    float d;
    float diff;
    float strength;

};


