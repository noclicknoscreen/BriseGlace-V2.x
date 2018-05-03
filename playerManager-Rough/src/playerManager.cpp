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
}

//--------------------------------------------------------------
void playerManager::update(){
    
    string url = "https://localhost:8443/players";
    
    if (response.open(url)){
        // update variables
        mLastMessage = response["lastMessage"]["text"].asString();
        mLastNumber = response["lastNumber"].asInt();
        // The log because we're happy
        ofLogNotice() << "Open Successful : [" << mLastNumber << ":" << mLastMessage << "]";
    }else{
        ofLogError() << "Unable to parse file";
    }

}

//--------------------------------------------------------------
void playerManager::draw(){
    
}
