//
//  PixelMode.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/15/15.
//
//

#include "PixelMode.h"


PixelMode::PixelMode(string _name, float _duration) : Mode(_name, _duration) {
    Tweenzor::init();
    grays = vector<int>(25*25*25*25*25);
    reset();
}


void PixelMode::update() {
    Tweenzor::update( ofGetElapsedTimeMillis() );
    
}


void PixelMode::draw() {
    ofPushMatrix();
    ofTranslate(0, y);
    ofPushStyle();
    drawPixels(pixSize);
    ofPopStyle();
    ofPopMatrix();
}


void PixelMode::reset() {
    y = 0;
    numSubdivs = 0;
    pixSize = 0;
    pixTimer = 0;
    subdivTimer = 0;
    Tweenzor::removeAllTweens();
    addFlash(0);
    
    freq = 60;
    Tweenzor::add(&freq, 60, 8, 0.f, 4.0f, EASE_OUT_EXPO);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&freq), this, &PixelMode::flashSlowComplete);
    
}

void PixelMode::addFlash(float* arg) {
    Tweenzor::removeTween(&pixTimer);
    Tweenzor::add(&pixTimer, 0, 1, 0.f, 1.0/freq, EASE_LINEAR);
    Tweenzor::getTween(&pixTimer)->setRepeat( 1, true );
    Tweenzor::addCompleteListener( Tweenzor::getTween(&pixTimer), this, &PixelMode::addFlash);
    
    setPixelColors(pixSize);
}

void PixelMode::drawPixels(float l) {
    if (l == 0) {
        if (pixTimer > 0.5) {
            ofBackground(255);
        } else {
            ofBackground(black);
        }
    }
    else {
        int k = 0;
        for (int i=0; i<ofGetWidth(); i+=l) {
            for (int j=0; j<5*ofGetHeight(); j+=l) {
                ofSetColor(grays[k]);
                ofRect(i, j, l, l);
                k++;
            }
        }
    }
}

void PixelMode::setPixelColors(float l) {
    if (l != 0) {
        int k = 0;
        for (int i=0; i<ofGetWidth(); i+=l) {
            for (int j=0; j<5*ofGetHeight(); j+=l) {
                grays[k] = ofRandom(1.0) > 0.5 ? 255 : 0;
                k++;
            }
        }
    }
}

void PixelMode::flashSlowComplete(float* arg) {
    Tweenzor::removeTween(&freq);
    subdivComplete(0);
}


void PixelMode::subdivComplete(float* arg) {
    ofLog() << "subdiv " << pixSize << "complete";
    Tweenzor::removeTween(&subdivTimer);
    if (numSubdivs < 6) { // split
        if (pixSize == 0) {
            pixSize = ofGetWidth();
        } else if (pixSize == ofGetWidth()) {
            pixSize /= 5;
        } else {
            pixSize /= 2;
        }
        
        setPixelColors(pixSize);
        Tweenzor::add(&subdivTimer, 0, 1, 0.f, 1.0f, EASE_LINEAR);
        Tweenzor::addCompleteListener( Tweenzor::getTween(&subdivTimer), this, &PixelMode::subdivComplete);
        numSubdivs++;
    } else { // slide
        Tweenzor::add(&y, 0, -4*ofGetHeight(), 0.f, 6.0f, EASE_IN_EXPO);
        Tweenzor::addCompleteListener( Tweenzor::getTween(&y), this, &PixelMode::slideComplete);
    }
}

void PixelMode::slideComplete(float* arg) {
    Tweenzor::removeTween(&y);
    ofLog() << "slide done";
}


void PixelMode::preExit() {
    Tweenzor::pauseAllTweens();
}

