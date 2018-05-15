//
//  playerManager.cpp
//  playerManager-Rough
//
//  Created by Sébastien Albert on 03/05/2018.
//
//

#include "playerManager.h"

//--------------------------------------------------------------
//void playerManager::setup(ofEvent<player> _someoneSpoke){
void playerManager::setup(){
    
    // 1st player is red
    mColors[1] = ofColor::red;
    mSequences[1] = "Cube-Rouge";
    mPositions[1] = ofPoint(200, ofGetHeight());
    // Green
    mColors[2] = ofColor::green;
    mSequences[2] = "Cube-Vert";
    mPositions[2] = ofPoint(0.5 * ofGetWidth(), ofGetHeight());
    // Blue
    mColors[3] = ofColor::blue;
    mSequences[3] = "Cube-Bleu";
    mPositions[3] = ofPoint(ofGetWidth() - 200, ofGetHeight());
    // MySelf = Gray
    mColors[4] = ofColor::gray;
    mSequences[4] = "Cube-Rouge";
    mPositions[4] = ofPoint(0.5 * ofGetWidth(), ofGetHeight());
    
    //    someoneSpoke = _someoneSpoke;
    ofRegisterURLNotification(this);
    freshRestart();
    
}

void playerManager::freshRestart(){
    ofLoadURLAsync("https://localhost:8443/resetPlayers","resetPlayers");
    bLoadingPlayers = true;
}

//--------------------------------------------------------------
void playerManager::update(){
    
    if(bLoadingPlayers == false){
        ofLoadURLAsync("https://localhost:8443/players","players");
        bLoadingPlayers = true;
    }
    
}

//--------------------------------------------------------------
void playerManager::loadPlayers(ofBuffer _datas){
    
    if (mResponse.openFromBuffer(_datas)){
        
        int nbPlayers = mResponse["players"].size();
        for (int idxPlayer = 0; idxPlayer < nbPlayers; ++idxPlayer)
        {
            // Does player exists ?
            int realNr = mResponse["players"][idxPlayer]["nr"].asInt();
            std::map<int, player>::iterator onePlayer = mPlayers.find(realNr);
            if (onePlayer != mPlayers.end()){
                //                ofLogNotice() << "Update player : " << mResponse["players"][idxPlayer]["nr"].asInt() <<
                //                ":" << mResponse["players"][idxPlayer]["isAvailable"].asBool() <<
                //                ":" << mResponse["players"][idxPlayer]["lastMessage"]["text"].asString() <<
                //                ":" << mResponse["players"][idxPlayer]["volume"].asFloat();
                //                // If yes, then update
                onePlayer->second.update(mResponse["players"][idxPlayer]["isAvailable"].asBool(),
                                         mResponse["players"][idxPlayer]["lastMessage"]["text"].asString(),
                                         mResponse["players"][idxPlayer]["lastMessage"]["textToCompare"].asString(),
                                         mResponse["players"][idxPlayer]["volume"].asFloat(),
                                         mResponse["players"][idxPlayer]["nr"].asInt());
                
            }else{
                
                ofLogNotice() << "Add player : " << mResponse["players"][idxPlayer]["nr"].asInt();
                // Else add
                player newPlayer = player(mColors[realNr], mSequences[realNr]);
                
                newPlayer.update(mResponse["players"][idxPlayer]["isAvailable"].asBool(),
                                 mResponse["players"][idxPlayer]["lastMessage"]["text"].asString(),
                                 mResponse["players"][idxPlayer]["lastMessage"]["textToCompare"].asString(),
                                 mResponse["players"][idxPlayer]["volume"].asFloat(),
                                 mResponse["players"][idxPlayer]["nr"].asInt());
                mPlayers.insert( std::pair<int,player>(realNr,newPlayer) );
            }
            
            
        }
        
        // Throw event when someone new spoke
        if(mLastTime != mResponse["lastMessage"]["time"].asString()){
            
            // update variables
            mLastMessage = mResponse["lastMessage"]["text"].asString();
            mLastTime = mResponse["lastMessage"]["time"].asString();
            mLastNumber = mResponse["lastNumber"].asInt();
            
            // Throw event
            std::map<int, player>::iterator onePlayer = mPlayers.find(mLastNumber);
            if (onePlayer != mPlayers.end()){
                if(onePlayer->second.getLastMessage() != ""){
                    ofNotifyEvent(someoneSpoke, onePlayer->second, this);
                }
            }
            
        }
        // The log because we're happy
        //ofLogNotice() << "Open Successful : [" << mLastNumber << ":" << mLastMessage << "] [nbPlayers:" << nbPlayers << "]";
        
    }else{
        ofLogError() << "Unable to parse file";
    }
    
}

//--------------------------------------------------------------
void playerManager::draw(){
    
    std::map<int, player>::iterator onePlayer;
    int count = 0;
    int border = 200;
    
    for (onePlayer=mPlayers.begin(); onePlayer!=mPlayers.end(); ++onePlayer){
        // Position is nearby middle, bottom
//        float x;
//        if(mPlayers.size() > 1){
//            x = ofMap((float)(count)/(float)(mPlayers.size() -1), 0, 1, border, ofGetWidth() - border);
//        }else{
//            x = ofMap(0.5, 0, 1, border, ofGetWidth() - border);
//        }
//        
//        ofVec2f pos = ofVec2f(x, ofGetHeight());
        // Second is value (aka player)
        onePlayer->second.draw(mPositions[onePlayer->second.getNumber()]);
        // Then increase
        count++;
    }
}

//--------------------------------------------------------------
void playerManager::urlResponse(ofHttpResponse & response){
    
    if(response.status==200){
        //ofLogNotice() << "Request answer received : " << response.request.name;
        //        if(response.request.name == "players"){
        loadPlayers(response.data);
        bLoadingPlayers = false;
        //        }
    }else{
        ofLogError() << response.status << " " << response.error << endl;
    }
}

