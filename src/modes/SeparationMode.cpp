//
//  SeparationMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "SeparationMode.h"

SeparationMode::SeparationMode(string _name, float _duration, bool _useHR, int _color) : Mode(_name, _duration, _useHR) {
    //fadeEnter = true;
    color = _color;
    vehicles = vector<Vehicle>(400);
}


void SeparationMode::update() {
    for (int i = 0; i < vehicles.size(); i++) {
        vehicles[i].separate(vehicles);
        vehicles[i].update();
        vehicles[i].borders();
    }
    floorValue = 175*sin(0.1*hr*ofGetElapsedTimef()); //PEND
}


void SeparationMode::draw() {
    ofPushStyle();
    ofClear(abs(255-color), 255);
    for (int i = 0; i < vehicles.size(); i++) {
        vehicles[i].draw();
    }
    ofPopStyle();
}


void SeparationMode::reset() {
    for (int i = 0; i < vehicles.size(); i++) {
        float dir = ofRandom(1.0);
        if (dir < 0.25) { // top
            vehicles[i].setup(ofRandom(width), ofRandom(-height*1.1, -height*0.1), width, height, color);
        } else if (dir < 0.5) { // right
            vehicles[i].setup(ofRandom(width*1.1, width*2.1), ofRandom(height), width, height, color);
        } else if (dir < 0.75) { // bottom
            vehicles[i].setup(ofRandom(width), ofRandom(height*1.1, height*2.1), width, height, color);
        } else { // left
            vehicles[i].setup(ofRandom(-width*1.1, -width*0.1), ofRandom(height), width, height, color);
        }
    }
}

void SeparationMode::preExit() {
}



