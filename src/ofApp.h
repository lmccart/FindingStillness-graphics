#pragma once

#include "ofMain.h"
#include "ModeManager.h"
#include "ofxOscReceiver.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void mouseMoved(int x, int y );
    void mousePressed(int x, int y, int button);
    
private:
    ModeManager modeManager;
    ofxOscReceiver oscReceiver;
    ofxOscMessage oscMessage;
//    ofShader shaderBlurX, shaderBlurY;
//    ofFbo fboBlurOnePass, fboBlurTwoPass;
};
