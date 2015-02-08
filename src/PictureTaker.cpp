//
//  PictureTaker.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/8/15.
//
//

#include "PictureTaker.h"


void PictureTaker::setup() {
    
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    if (devices.size() > 0) {
        
        cout << devices[0].id << ": " << devices[0].deviceName;
        if( devices[0].bAvailable ){
            vidGrabber.setDeviceID(devices[0].id);
            vidGrabber.initGrabber(320, 240);
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
    }
    
    
}

void PictureTaker::update() {
    vidGrabber.update();
}

void PictureTaker::takePic() {
    ofLog() << "take pic";
    image.setFromPixels(vidGrabber.getPixels(), vidGrabber.width, vidGrabber.height, OF_IMAGE_COLOR);
    image.saveImage(ofToString(ofGetElapsedTimef(), 0));
}

