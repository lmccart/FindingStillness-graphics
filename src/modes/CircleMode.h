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
        void update();
        void draw();
        void reset();
        void preExit();
        
        
    private:
        float diameter;
        float scale;

};


