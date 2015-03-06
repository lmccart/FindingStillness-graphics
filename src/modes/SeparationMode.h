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
    int type;
    int color;
    float baser;
    float w, h;
    
    void setup(float x, float y, float _w, float _h, int c) {
        color = c;
        w = _w;
        h = _h;
        position.set(x, y);
        velocity.set(w*0.5-x, h*0.5-y);
        acceleration.set(0, 0);
        r = 25;
        maxspeed = 5;    // Maximum speed
        maxforce = 0.2;  // Maximum steering force
        maxradius = 25;
        baser = 25;
        type = floor(ofRandom(4));
    }
    
    void applyForce(ofVec2f force) {
        acceleration += force;
    }
    
    // Separation
    // Method checks for nearby vehicles and steers away
    void separate(vector<Vehicle> vehicles) {
        ofVec2f sum;
        int count = 0;
        // For every boid in the system, check if it's too close
        for (int i = 0; i < vehicles.size(); i++) {
            float d = position.distance(vehicles[i].position);
            // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
            if ((d > 0) && (d < 3*(r+vehicles[i].r))) {
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
        if (baser < 32.5) {
            baser += 0.03;
        } else {
            baser += 0.2;
        }
        
        // Update velocity
        velocity += 0.25*acceleration;
        // Limit speed
        velocity.limit(maxspeed);
        position += velocity;
        // Reset accelertion to 0 each cycle
        acceleration.set(0, 0);
        maxradius += 0.05;
        
        float d = sqrt(pow(abs(w*0.5-position.x), 2)+pow(abs(h*0.5-position.y), 2));
        d = ofMap(d, 0, w, 2.0, 0.1);
        r = MAX(baser, baser*d);
    }
    
    void draw() {
        ofSetColor(color);
        ofPushMatrix();
        ofTranslate(position.x, position.y);
//        ofEllipse(0, 0, r, r);
        
        ofVec2f zero(0, -1);
        float theta = zero.angle(velocity);
        ofRotate(theta);
        if (type == 0) {
            ofTriangle(0, -r*2, -r, r, r, r);
        } else if (type == 1) {
            ofRect(-r, -r, 2*r, 2*r);
        } else if (type == 2) {
            ofTriangle(0, -r*2, -r, r, r, r);
        } else if (type == 3) {
            ofRect(-r, -1.5*r, 2*r, 3*r);
        }
        
        
        ofPopMatrix();
    }
    
    // Wraparound
    void borders() {
        if (position.x < -r)  velocity.x = abs(velocity.x);//position.x = width +r;
        if (position.y < -r)  velocity.y  = abs(velocity.y);//position.y = height +r;
        if (position.x > w +r) velocity.x = -abs(velocity.x);//position.x = -r;
        if (position.y > h +r) velocity.y = -abs(velocity.y);//position.y = -r;
    }
};

class SeparationMode : public Mode {

public:
    SeparationMode(string _name, float _duration, bool _useHR, int _color);
    void update();
    void draw();
    void reset();
    void preExit();
    
    
private:
    vector<Vehicle> vehicles;
    int color;
};


