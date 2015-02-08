//
//  Server.h
//  FindingStillness
//
//  Created by Lauren McCarthy on 2/8/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxHttp.h"
#include "ofxJSON.h"

class Server {
    
public:
    void setup();
    void update();
    
    void ping();
    void onHTTPPostEvent(ofx::HTTP::PostEventArgs& evt);
    void onHTTPFormEvent(ofx::HTTP::PostFormEventArgs& evt);
    void onHTTPUploadEvent(ofx::HTTP::PostUploadEventArgs& evt);

    
private:
    ofx::HTTP::BasicPostServer::SharedPtr server;
    ofxJSONElement json;

};
