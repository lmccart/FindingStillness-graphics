//
//  CircleMode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "ofMain.h"
#include "Mode.h"

class CircleMode : public Mode {
    
public:
    CircleMode(float duration);
    virtual void enter();
    virtual void update();
    virtual void draw();
    virtual void reset();
    virtual void preExit();
    void exit();
    
    
private:
};


