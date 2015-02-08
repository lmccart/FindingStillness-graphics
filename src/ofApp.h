#pragma once

#include "ofMain.h"
#include "ModeManager.h"
#include "Server.h"
#include "PictureTaker.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void mouseMoved(int x, int y );
    void mousePressed(int x, int y, int button);
    void gotMessage(ofMessage msg);
    
private:
    ModeManager modeManager;
    Server server;
    PictureTaker picTaker;
};
