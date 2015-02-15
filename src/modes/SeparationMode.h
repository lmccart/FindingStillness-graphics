//
//  SeparationMode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/7/15.
//
//
#pragma once

#include "ofMain.h"
#include "Mode.h"


// Vehicle object


class Vehicle {
public:
    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
    float r;
    float maxspeed;
    float maxforce;
    float maxradius;
    
    void setup(float x, float y) {
        position.set(x, y);
        velocity.set(0, 0);
        acceleration.set(0, 0);
        r = 25;
        maxspeed = 2;    // Maximum speed
        maxforce = 0.1;  // Maximum steering force
        maxradius = 25;
    }
    
    void applyForce(ofVec2f force) {
        acceleration += force;
    }
    
    // Separation
    // Method checks for nearby vehicles and steers away
    void separate(vector<Vehicle> vehicles) {
        float desiredseparation = r;
        ofVec2f sum;
        int count = 0;
        // For every boid in the system, check if it's too close
        for (int i = 0; i < vehicles.size(); i++) {
            float d = position.distance(vehicles[i].position);
            // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
            if ((d > 0) && (d < r+vehicles[i].r)) {
                // Calculate vector pointing away from neighbor
                ofVec2f diff = position - vehicles[i].position;
                diff.normalize();
                diff /= d;        // Weight by distance
                sum += diff;
                count++;            // Keep track of how many
            }
        }
        // Average -- divide by how many
        if (count > 0) {
            sum /= count;
            // Our desired vector is the average scaled to maximum speed
            sum.normalize();
            sum *= maxspeed;
            // Implement Reynolds: Steering = Desired - Velocity
            ofVec2f steer = sum - velocity;
            steer.limit(maxforce);
            applyForce(steer);
        }
    }
    
    // Method to update location
    void update() {
        // Update velocity
        velocity += acceleration;
        // Limit speed
        velocity.limit(maxspeed);
        position += velocity;
        // Reset accelertion to 0 each cycle
        acceleration.set(0, 0);
        maxradius += 0.05;
    }
    
    void draw() {
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(position.x, position.y);
//        ofEllipse(0, 0, r, r);
        
        ofVec2f zero(0, -1);
        float theta = zero.angle(velocity);
        ofRotate(theta);
        ofTriangle(0, -r*2, -r, r*2, r, r*2);
        
        
        ofPopMatrix();
    }
    
    // Wraparound
    void borders() {
        
        if (position.x < -r) position.x = ofGetWidth()+r;
        if (position.y < -r) position.y = ofGetHeight()+r;
        if (position.x > ofGetWidth()+r) position.x = -r;
        if (position.y > ofGetHeight()+r) position.y = -r;
    }
};

class SeparationMode : public Mode {
    
    public:
        SeparationMode(string _name, float _duration);
        void update();
        void draw();
        void reset();
        void preExit();
        
        
    private:
        vector<Vehicle> vehicles;
};


