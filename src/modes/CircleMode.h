//
//  CircleMode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#pragma once

#include "ofMain.h"
#include "Mode.h"

class CircleMode : public Mode {
    
public:
    CircleMode(string _name, float _duration);
    void update(float hr);
    void draw();
    void reset();
    void preExit();
    
    
private:
    float diameter;
    float scale;
    ofImage img;

};


