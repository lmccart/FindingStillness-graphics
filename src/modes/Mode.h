//
//  Mode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "ofMain.h"
#include "ofxTweenzor.h"

class Mode {
    
public:
    Mode(float duration);
    virtual void enter();
    virtual void update();
    virtual void draw();
    virtual void preExit();
    virtual void reset();
    void exit();
    
    bool playing;
    float duration;
    float black;

    
private:
    float fadeInTime;
};


