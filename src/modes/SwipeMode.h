//
//  SwipeMode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#pragma once

#include "ofMain.h"
#include "Mode.h"

class SwipeMode : public Mode {
    
public:
    SwipeMode(string _name, float _duration);
    void update(float hr);
    void draw();
    void reset();
    void preExit();
    
    
private:
    float y;
    float dir;

};


