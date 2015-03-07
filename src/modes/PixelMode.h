//
//  PixelMode.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/15/15.
//
//

#pragma once

#include "ofMain.h"
#include "Mode.h"


class Oscillator {
private:
    float offset = 0;
    float fadeInTime = 0;
public:
    int x, y;
    float startTime = 0;
    float speed = 1;
    float alpha;
    float brightness;
    Oscillator(int x, int y) : x(x), y(y) {
        offset = ofRandom(1);
        fadeInTime = ofRandom(.5, 2);
    }
    
    
    float cospp(float x) {
        return (cos(x * TWO_PI) + 1) / 2;
    }

    void draw(float time) {
        alpha = MIN(1, (time - startTime) / fadeInTime);
        float localTime = time + offset;
        brightness = cospp(localTime * speed);
        ofSetColor(brightness * 255, alpha * 255);
        ofRect(x, y, 1, 1);
    }
};

class OscillatorGrid {
public:
    int width, height;
    vector<Oscillator> inactive, active;
    void setup(int width, int height) {
        this->width = width;
        this->height = height;
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                inactive.push_back(Oscillator(x, y));
            }
        }
        ofRandomize(inactive);
    }
    bool exhausted() {
        return inactive.empty();
    }
    bool poke(float time, float speed) {
        if(exhausted()) {
            return false;
        }
        active.push_back(inactive.back());
        inactive.pop_back();
        active.back().startTime = time;
        active.back().speed = speed;
        return true;
    }
    void draw(float time) {
        for(int i = 0; i < active.size(); i++) {
            active[i].draw(time);
        }
    }
};

class OscillatorStack {
public:
    vector<OscillatorGrid> grids;
    void setup(int levels) {
        grids.resize(levels);
        for(int i = 0; i < levels; i++) {
            int n = 1 << i;
            grids[i].setup(n, n);
        }
    }
    int exhaustion() {
        for(int i = 0; i < grids.size(); i++) {
            if(!grids[i].exhausted()) {
                return i;
            }
        }
        return grids.size();
    }
    bool exhausted() {
        return exhaustion() == grids.size();
    }
    bool poke(float time, float speed) {
        for(int i = 0; i < grids.size(); i++) {
            if(grids[i].poke(time, speed)) {
                return true;
            }
        }
        return false;
    }
    void draw(float time) {
        ofPushMatrix();
        for(int i = 0; i < grids.size(); i++) {
            grids[i].draw(time);
            ofScale(.5, .5);
        }
        ofPopMatrix();
    }
};


class PixelMode : public Mode {
    
public:
    PixelMode(string _name, float _duration, bool _useHR);
    void start();
    void update();
    void draw();
    void reset();
    void preExit();
    float fadeMult;
    
private:
    OscillatorStack ost;
};


