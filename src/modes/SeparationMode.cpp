//
//  SeparationMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "SeparationMode.h"

SeparationMode::SeparationMode(string _name, float _duration) : Mode(_name, _duration) {
    reset();
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
    ofBackground(black);
    for (int i = 0; i < vehicles.size(); i++) {
        vehicles[i].draw();
    }
    ofPopStyle();
}


void SeparationMode::reset() {
    vehicles = vector<Vehicle>(50);
    for (int i = 0; i < vehicles.size(); i++) {
        vehicles[i].setup(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    }
}

void SeparationMode::preExit() {
}



