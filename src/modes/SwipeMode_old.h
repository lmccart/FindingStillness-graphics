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
    SwipeMode(string _name, float _duration, bool _useHR);
    void update();
    void draw();
    void reset();
    void preExit();
    
    void onComplete(float* arg);
    
    
private:
    float x, y;

};


