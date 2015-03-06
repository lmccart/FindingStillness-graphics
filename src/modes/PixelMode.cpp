//
//  PixelMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/15/15.
//
//

#include "PixelMode.h"


PixelMode::PixelMode(string _name, float _duration, bool _useHR) : Mode(_name, _duration, _useHR) {
}


void PixelMode::update() {
    
    float speed = 60 / hr;
    float time = ofGetElapsedTimef();
    float pps;
    if(!ost.exhausted()) {
        // pokes per second is based on how deep we are
        pps = 1 << ost.exhaustion();
        // pokes per second increases exponentially
        pps *= pps;
        // but we slow it down a bit
        pps *= .5;
        // pokes per frame is based on the framerate
        float ppf = pps / ofGetFrameRate();
        // if pokes per frame is less than 1
        if(ppf < 1) {
            // we poke probablistically
            if(ofRandom(1) < ppf) {
                ost.poke(time, speed);
            }
        } else {
            // otherwise we poke ppf times
            for(int i = 0; i < ppf; i++) {
                ost.poke(time, speed);
            }
        }
    }
    
    if (ost.grids[0].active.size() > 0) { //pend
        if (getModeElapsedTime() < 0.5*duration) {
            floorValue = floor(ost.grids[0].active[0].brightness+0.5)*100;
        } else {
            floorValue = ost.grids[0].active[0].brightness*100;
        }
    } else {
        floorValue = 0;
    }
}


void PixelMode::draw() {
    int side = MAX(width, height);
    // center
    ofTranslate((width - side) / 2, (height - side) / 2);
    ofScale(side, side);
    ost.draw(ofGetElapsedTimef());
}


void PixelMode::reset() {
    ost = OscillatorStack();
    ost.setup(6);
    ost.poke(ofGetElapsedTimef(), 1);
}

void PixelMode::preExit() {
}

