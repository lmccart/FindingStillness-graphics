//
//  ModeManager.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "ofMain.h"
#include "Mode.h"


class ModeManager {
    
public:
    
    void setup();
    void update();
    void draw();
    void reset();
    void start();
    void next();
    
private:
    bool playing;
    int curMode;
    float modeStartTime;
    vector<Mode*> modes;

};
