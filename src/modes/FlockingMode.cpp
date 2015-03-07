//
//  FlockingMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//

#include "FlockingMode.h"

FlockingMode::FlockingMode(string _name, float _duration, bool _useHR) : Mode(_name, _duration, _useHR) {
    fadeEnter = true;
    fadeExit = true;
    fbo.allocate(width, height, GL_RGBA);
    fbo.begin();
    ofClear(0, 255);
    fbo.end();
}


void FlockingMode::update() {
    for (int i = 0; i < boids.size(); i++) {
        boids[i].run(boids);  // Passing the entire list of boids to each boid individually
    }
    floorValue = 125*sin(0.1*hr*ofGetElapsedTimef()); //PEND
}


void FlockingMode::draw() {
    fbo.begin();
        ofPushStyle();
        ofSetColor(0, 5);
        ofRect(0, 0, width, height);
        for (int i = 0; i < boids.size(); i++) {
            boids[i].draw();
        }
        ofPopStyle();
    fbo.end();
    
    ofPushStyle();
    //ofSetColor(255);
    fbo.draw(0,0);
    ofPopStyle();
//
//    ofPushStyle();
//    ofSetColor(255, 0, 0);
//    ofRect(0, 0, width/2, height/2);
//    ofPopStyle();
}


void FlockingMode::reset() {
    boids = vector<Boid>(250);
    float d = boids.size()*height*0.4/width;
    float x = 0, y = 0;
    for (int i = 0; i < boids.size(); i++) {
        
        boids[i].setup(x, y, width, height);
        x += d;
        if (x >= width) {
            x = 0;
            y += d;
        }
    }
    
        
//        float dir = ofRandom(1.0);
//        if (dir < 0.25) { // top
//            boids[i].setup(ofRandom(width), ofRandom(-height*0.5), width, height);
//        } else if (dir < 0.5) { // right
//            boids[i].setup(ofRandom(width, width*1.5), ofRandom(height), width, height);
//        } else if (dir < 0.75) { // bottom
//            boids[i].setup(ofRandom(width), ofRandom(height, height*1.5), width, height);
//        } else { // left
//            boids[i].setup(ofRandom(-width*0.5, 0), ofRandom(height), width, height);
//        }
//    }
    fbo.begin();
    ofClear(0);
    fbo.end();
}

void FlockingMode::preExit() {
}



