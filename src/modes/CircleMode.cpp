//
//  CircleMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "CircleMode.h"

CircleMode::CircleMode(string _name, float _duration) : Mode(_name, _duration) {
    img.loadImage("imgs/ellipse2.png");
}


void CircleMode::update(float hr) {
}


void CircleMode::draw() {
    ofPushStyle();
    ofClear(black, 255);
    ofSetColor(255);
    //ofEllipse(width/2, height/2, scale*diameter, scale*diameter);
    float d = scale*diameter;
    img.draw(width/2-d/2, height/2-d/2, d, d);
    ofPopStyle();
}


void CircleMode::reset() {
    diameter = 0;
    scale = 0;
    Tweenzor::add(&scale, 0, 1.25, 0.f, 15.0f, EASE_LINEAR);
    Tweenzor::add(&diameter, 0, width*1.3, 0.f, 1.f, EASE_IN_OUT_QUAD);
    Tweenzor::getTween(&diameter)->setRepeat( -1, true );
    Tweenzor::getTween(&scale)->setRepeat( -1, true );
}

void CircleMode::preExit() {
    Tweenzor::removeTween(&scale);
    Tweenzor::removeTween(&diameter);
}

