//
//  Mode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "Mode.h"

Mode::Mode(float duration) {
    duration = duration;
    
    playing = false;
    black = 0;
    fadeInTime = 1000;
}

void Mode::enter() {
    ofLog() << "enter0";
}

void Mode::exit() {
    
}