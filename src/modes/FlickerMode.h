//
//  FlickerMode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/15/15.
//
//

#pragma once

#include "ofMain.h"
#include "Mode.h"

class FlickerMode : public Mode {
    
    public:
        FlickerMode(string _name, float _duration);
        void update();
        void draw();
        void reset();
        void preExit();
        
        

};


