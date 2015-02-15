//
//  FlockingMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "FlockingMode.h"

FlockingMode::FlockingMode(string _name, float _duration) : Mode(_name, _duration) {
    reset();
}


void FlockingMode::update() {
    for (int i = 0; i < boids.size(); i++) {
        boids[i].run(boids);  // Passing the entire list of boids to each boid individually
    }
}


void FlockingMode::draw() {
    ofBackground(black);
    for (int i = 0; i < boids.size(); i++) {
        boids[i].draw();
    }
}


void FlockingMode::reset() {
    boids = vector<Boid>(200);
    for (int i = 0; i < boids.size(); i++) {
        float dir = ofRandom(1.0);
        if (dir < 0.25) { // top
            boids[i].setup(ofRandom(ofGetWidth()), ofRandom(-ofGetHeight()*0.15));
        } else if (dir < 0.5) { // right
            boids[i].setup(ofRandom(ofGetWidth(), ofGetWidth()*1.15), ofRandom(ofGetHeight()));
        } else if (dir < 0.75) { // bottom
            boids[i].setup(ofRandom(ofGetWidth()), ofRandom(ofGetHeight(), ofGetHeight()*1.15));
            
        } else { // left
            boids[i].setup(ofRandom(-ofGetWidth()*0.15, 0), ofRandom(ofGetHeight()));
            
        }
    }
}

void FlockingMode::preExit() {
}



