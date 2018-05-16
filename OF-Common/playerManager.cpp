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
    
    //gui
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    
    gui.add(player1.set("player1",ofColor(000,228,255),ofColor(0,0),ofColor(255,255)));
    gui.add(player2.set("player2",ofColor(255,042,140),ofColor(0,0),ofColor(255,255)));
    gui.add(player3.set("player3",ofColor(182,064,167),ofColor(0,0),ofColor(255,255)));
    gui.add(ipAdress.set("ipAdress", "localhost"));
    
    gui.loadFromFile("settingsPlayers.xml");
    drawGui = false;

    
    // 1st player is red
    mColors[1] = player1;
    mSequences[1] = "Cube-Bleu";
    mPositions[1] = ofPoint(200, ofGetHeight());
    // Green
    mColors[2] = player2;
    mSequences[2] = "Cube-Rouge";
    mPositions[2] = ofPoint(0.5 * ofGetWidth(), ofGetHeight());
    // Blue
    mColors[3] = player3;
    mSequences[3] = "Cube-Violet";
    mPositions[3] = ofPoint(ofGetWidth() - 200, ofGetHeight());
    // MySelf = Gray
    mColors[4] = player1;
    mSequences[4] = "Cube-Rouge";
    mPositions[4] = ofPoint(0.5 * ofGetWidth(), ofGetHeight());
    
    //    someoneSpoke = _someoneSpoke;
    ofRegisterURLNotification(this);
    freshRestart();
    
}

//--------------------------------------------------------------
void playerManager::freshRestart(){
    if(bLoadingPlayers == false){
        string url = "https://" + ipAdress.get() + ":8443/resetPlayers";
        ofLoadURLAsync(url,"resetPlayers");
        bLoadingPlayers = true;
    }
}

//--------------------------------------------------------------
void playerManager::update(){
    if(bLoadingPlayers == false){
        string url = "https://" + ipAdress.get() + ":8443/players";
        ofLoadURLAsync(url,"players");
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
                
                // If yes, then update
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
float playerManager::getSumVolume()
{
    float sumVolume=0;
    for(std::map<int,player>::iterator it=mPlayers.begin(); it!=mPlayers.end(); it++)
    {
        sumVolume += it->second.getVolume();
    }
    return sumVolume;
}

//--------------------------------------------------------------
float playerManager::getAverageVolume()
{
    float sumVolume=0;
    int nbP=0;
    
    for(std::map<int,player>::iterator it=mPlayers.begin(); it!=mPlayers.end(); it++)
    {
        sumVolume += it->second.getVolume();
        nbP++;
    }
    if(!(nbP>0))
        return 0;
    else
        return sumVolume/nbP;
}


//--------------------------------------------------------------
void playerManager::draw(){
    
    std::map<int, player>::iterator onePlayer;
    int count = 0;
    int border = 200;
    
    for (onePlayer=mPlayers.begin(); onePlayer!=mPlayers.end(); ++onePlayer){
        // Second is value (aka player)
        onePlayer->second.draw(mPositions[onePlayer->second.getNumber()]);
        // Then increase
        count++;
    }
    
    if(drawGui){
        gui.draw();
    }
}

//--------------------------------------------------------------
void playerManager::urlResponse(ofHttpResponse & response){
    
    if(response.status == 200){
        if(response.request.name == "players"){
            
            //if(ofGetFrameNum() %5 == 0)
            //{
                loadPlayers(response.data);
            //}
        }else{
            ofLogNotice() << "Request answer received : " << response.request.name;
        }
        
        bLoadingPlayers = false;
        
    }else{
        ofLogError() << response.status << " " << response.error << endl;
    }
}

//--------------------------------------------------------------
void playerManager::keyPressed(int key){
    
    if( key == 'h' ){
        ofLog() << "M'entends tu ???????";
        drawGui = !drawGui;
    }
    
    if(key == 's') {
        gui.saveToFile("settingsPlayers.xml");
    }
    
    if(key == 'l') {
        gui.loadFromFile("settingsPlayers");
    }
}

