//
//  Mode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "ofMain.h"

class Mode {
    
public:
    Mode(float duration);
    void enter();
    void update();
    void draw();
    void preExit();
    void exit();
    
    bool playing;
    float duration;
    
    
private:
    float black;
    float fadeInTime;
};


