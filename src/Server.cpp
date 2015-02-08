//
//  Server.cpp
//  Finding Stillness
//
//  Created by Lauren McCarthy on 2/8/15.
//
//

#include "Server.h"


void Server::setup() {
    
    ofx::HTTP::BasicPostServerSettings settings;
    
    // Many other settings are available.
    settings.setPort(3001);
    
    // Apply the settings.
    server = ofx::HTTP::BasicPostServer::makeShared(settings);
    
    // The client can listen for POST form and multi-part upload events.
    // User be aware, these methods are called from other threads.
    // The user is responsible for protecting shared resources (e.g. ofMutex).
    server->getPostRoute()->registerPostEvents(this);
    
    
//    server->registerMethod("ping",
//                           "Send a JSONRPC Ping Notification",
//                           this,
//                           &Server::ping);
    
    //settings.set
    
    // Start the server.
    server->start();
    
    ofLog() << (server->getURL());

}

void Server::update() {

}

void Server::ping() {
    ofLog() << "ping";
}


void Server::onHTTPPostEvent(ofx::HTTP::PostEventArgs& args)
{
    ofLogNotice("ofApp::onHTTPPostEvent") << "Data: " << args.getBuffer().getText();
    args.response.set("ok", "yes");
    args.response.send();
    //args.getRequest().response();
}


void Server::onHTTPFormEvent(ofx::HTTP::PostFormEventArgs& args)
{
    ofLogNotice("ofApp::onHTTPFormEvent") << "";
    ofx::HTTP::HTTPUtils::dumpNameValueCollection(args.getForm(), ofGetLogLevel());
    
    const char* data = "test";
    
    
    args.response.set("Access-Control-Allow-Origin", "*");
    args.response.add("Data", "yes");
    args.response.set("data", "yes");
    args.response.set("responseText", "ohyes");
 
    args.response.sendBuffer(data, strlen(data));
    args.response.send();
}


void Server::onHTTPUploadEvent(ofx::HTTP::PostUploadEventArgs& args)
{
    std::string stateString = "";
    
    switch (args.getState())
    {
        case ofx::HTTP::PostUploadEventArgs::UPLOAD_STARTING:
            stateString = "STARTING";
            break;
        case ofx::HTTP::PostUploadEventArgs::UPLOAD_PROGRESS:
            stateString = "PROGRESS";
            break;
        case ofx::HTTP::PostUploadEventArgs::UPLOAD_FINISHED:
            stateString = "FINISHED";
            break;
    }
    
    ofLogNotice("ofApp::onHTTPUploadEvent") << "";
    ofLogNotice("ofApp::onHTTPUploadEvent") << "         state: " << stateString;
    ofLogNotice("ofApp::onHTTPUploadEvent") << " formFieldName: " << args.getFormFieldName();
    ofLogNotice("ofApp::onHTTPUploadEvent") << "orig. filename: " << args.getOriginalFilename();
    ofLogNotice("ofApp::onHTTPUploadEvent") <<  "      filename: " << args.getFilename();
    ofLogNotice("ofApp::onHTTPUploadEvent") <<  "      fileType: " << args.getFileType().toString();
    ofLogNotice("ofApp::onHTTPUploadEvent") << "# bytes xfer'd: " << args.getNumBytesTransferred();
}
