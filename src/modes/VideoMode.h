//
//  VideoMode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//
#pragma once

#include "ofMain.h"
#include "Mode.h"

class VideoMode : public Mode {
    
    public:
        VideoMode(string _name, float _duration, string file);
        void update();
        void draw();
        void reset();
        void preExit();
        
        
    private:
        ofVideoPlayer videoPlayer;

};


