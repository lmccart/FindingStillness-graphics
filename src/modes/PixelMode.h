//
//  PixelMode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/15/15.
//
//

#pragma once

#include "ofMain.h"
#include "Mode.h"



class PixelMode : public Mode {
    
public:
    PixelMode(string _name, float _duration);
    void update();
    void draw();
    void reset();
    void preExit();
    
    void addFlash(float* arg);
    void flashSlowComplete(float* arg);
    void subdivComplete(float* arg);
    void slideComplete(float* arg);
    
    void setPixelColors(float l);
    void drawPixels(float l);
    
    
private:
    float y;
    vector<int> grays;
    float freq;
    float pixTimer;
    float subdivTimer;
    float pixSize;
    int numSubdivs;
};


