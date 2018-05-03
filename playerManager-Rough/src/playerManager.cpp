//
//  playerManager.cpp
//  playerManager-Rough
//
//  Created by Sébastien Albert on 03/05/2018.
//
//

#include "playerManager.h"

//--------------------------------------------------------------
void playerManager::setup(){
    // Register callback
    ofRegisterURLNotification(this);
    
}

//--------------------------------------------------------------
void playerManager::urlResponse(ofHttpResponse & response){
    // Get the response and do the job
    if(response.status==200 && response.request.name == "players"){
        // We get something
        ofLog() << "HTTP Response : ";
        ofLog() << response.data;
        // Flag off
        mHttpLoading=false;
    }else{
        ofLogError() << ofToString(response.status) << " " << response.error;
        if(response.status!=-1) mHttpLoading=false;
    }
}

//--------------------------------------------------------------
void playerManager::update(){
    
    // If flagged off, send request each update
    if(mHttpLoading == false){
        ofLoadURLAsync("https://localhost:8443/players","players");
        mHttpLoading = true;
    }
}

//--------------------------------------------------------------
void playerManager::draw(){
    
}
