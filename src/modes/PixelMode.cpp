//
//  PixelMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/15/15.
//
//

#include "PixelMode.h"


PixelMode::PixelMode(string _name, float _duration) : Mode(_name, _duration) {
}


void PixelMode::update() {
    
    float speed = 60 / hr;
    float time = ofGetElapsedTimef();
    if(!ost.exhausted()) {
        // pokes per second is based on how deep we are
        float pps = 1 << ost.exhaustion();
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
}


void PixelMode::draw() {
    int width = ofGetWidth();
    int height = ofGetHeight();
    int side = MAX(width, height);
    // center
    ofTranslate((width - side) / 2, (height - side) / 2);
    ofScale(side, side);
    ost.draw(ofGetElapsedTimef());
}


void PixelMode::reset() {
    ost = OscillatorStack();
    ost.setup(6);
}

void PixelMode::preExit() {
}

