//
//  PictureTaker.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/8/15.
//
//

#pragma once

#include "ofMain.h"

class PictureTaker {
    
public:
    void setup();
    void update();
    void takePic();

    
private:
    ofVideoGrabber vidGrabber;
    ofImage image;  
};
