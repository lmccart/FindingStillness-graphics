//
//  ModeManager.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#pragma once

#include "ofMain.h"
#include "CircleMode.h"
#include "FaderMode.h"
#include "VideoMode.h"
#include "SeparationMode.h"
#include "FlockingMode.h"


class ModeManager {
    
    public:
        
        void setup();
        void update();
        void draw();
        void reset();
        void start();
        void next(int i);
        
    private:
        bool playing;
        int curMode;
        float modeStartTime;
        vector<Mode*> modes;

};
