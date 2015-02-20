//
//  SeparationMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "SeparationMode.h"

SeparationMode::SeparationMode(string _name, float _duration, bool _useHR, int _color) : Mode(_name, _duration, _useHR) {
    color = _color;
}


void SeparationMode::update() {
    for (int i = 0; i < vehicles.size(); i++) {
        vehicles[i].separate(vehicles);
        vehicles[i].update();
        vehicles[i].borders();
    }
}


void SeparationMode::draw() {
    ofPushStyle();
    ofBackground(abs(255-color));
    for (int i = 0; i < vehicles.size(); i++) {
        vehicles[i].draw();
    }
    ofPopStyle();
}


void SeparationMode::reset() {
    vehicles = vector<Vehicle>(450);
    for (int i = 0; i < vehicles.size(); i++) {
        float dir = ofRandom(1.0);
        if (dir < 0.25) { // top
            vehicles[i].setup(ofRandom(ofGetWidth()), ofRandom(-ofGetHeight()*1), color);
        } else if (dir < 0.5) { // right
            vehicles[i].setup(ofRandom(ofGetWidth(), ofGetWidth()*2), ofRandom(ofGetHeight()), color);
        } else if (dir < 0.75) { // bottom
            vehicles[i].setup(ofRandom(ofGetWidth()), ofRandom(ofGetHeight(), ofGetHeight()*2), color);
        } else { // left
            vehicles[i].setup(ofRandom(-ofGetWidth()*1, 0), ofRandom(ofGetHeight()), color);
        }
    }
}

void SeparationMode::preExit() {
}



