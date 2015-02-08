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
        boids[i].maxforce = 0.05 + 0.3*sin(ofGetFrameNum()*0.01+100);
    }
}


void FlockingMode::draw() {
    ofBackground(black);
    for (int i = 0; i < boids.size(); i++) {
        boids[i].draw();
    }
}


void FlockingMode::reset() {
    boids = vector<Boid>(100);
    for (int i = 0; i < boids.size(); i++) {
        boids[i].setup(ofGetWidth()/2, ofGetHeight()/2);
    }
}

void FlockingMode::preExit() {
}



