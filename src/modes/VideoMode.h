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
    VideoMode(string _name, float _duration);
    void start();
    void update(float hr);
    void draw();
    void reset();
    void preExit();
        
        
private:
    ofVideoPlayer videoPlayer;

};


