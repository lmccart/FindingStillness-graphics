//
//  WashMode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/15/15.
//
//

#pragma once

#include "ofMain.h"
#include "Mode.h"

class WashMode : public Mode {
    
public:
    WashMode(string _name, float _duration, bool _useHR, int _color);
    void update();
    void draw();
    void reset();
    void preExit();
    
    
private:
    int color;

};


