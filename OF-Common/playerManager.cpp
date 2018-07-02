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
    gui.setup("Players"); // most of the time you don't need a name but don't forget to call setup
    
    gui.add(player1.set("player1",ofColor(000,228,255),ofColor(0,0),ofColor(255,255)));
    gui.add(player2.set("player2",ofColor(255,042,140),ofColor(0,0),ofColor(255,255)));
    gui.add(player3.set("player3",ofColor(182,064,167),ofColor(0,0),ofColor(255,255)));
    gui.add(ipAdress.set("ipAdress", "localhost"));
    
    gui.loadFromFile(settingsPlayers);
    drawGui = false;

    
    // 1st player is blue
    mColors[1] = player1;
    mSequencesPath[1] = "Cube-Bleu";
    mBullesPath[1] = "Bulles/BulleGauche.png";
    mPositions[1] = ofPoint(450, ofGetHeight() + 20);
    mBullesPos[1] = ofPoint(- 325, 190);
    // Red
    mColors[2] = player2;
    mSequencesPath[2] = "Cube-Rouge";
    mBullesPath[2] = "Bulles/BulleDroite.png";
    mPositions[2] = ofPoint(0.5 * ofGetWidth() - 75, ofGetHeight() + 20);
    mBullesPos[2] = ofPoint(125, 175);
//    mBullesPos[2] = ofPoint(- 310, 180);
    // Purple
    mColors[3] = player3;
    mSequencesPath[3] = "Cube-Violet";
    mBullesPath[3] = "Bulles/BulleDroite.png";
    mPositions[3] = ofPoint(ofGetWidth() - 450, ofGetHeight() + 20);
    mBullesPos[3] = ofPoint(120, 150);
    // MySelf = Gray
    mColors[4] = player1;
    mSequencesPath[4] = "Cube-Rouge";
    mBullesPath[4] = "Bulles/BulleCentre.png";
    mPositions[4] = ofPoint(0.5 * ofGetWidth(), ofGetHeight() + 20);
    mBullesPos[4] = ofPoint(- 310, 180);
    
    //    someoneSpoke = _someoneSpoke;
    ofRegisterURLNotification(this);
    freshRestart();
    
    // Players for FORCE DRAW (Drawing player not available
    mPlayers[1] = player(1, mPositions[1], mColors[1], mSequencesPath[1], mBullesPath[1]);
    mPlayers[2] = player(2, mPositions[2], mColors[2], mSequencesPath[2], mBullesPath[2]);
    mPlayers[3] = player(3, mPositions[3], mColors[3], mSequencesPath[3], mBullesPath[3]);
    
}

//--------------------------------------------------------------
void playerManager::freshRestart(){
    if(bResetPlayers == false){
        string url = "https://" + ipAdress.get() + ":8443/resetPlayers";
        ofLoadURLAsync(url,"resetPlayers");
        bResetPlayers = true;
    }
}

//--------------------------------------------------------------
void playerManager::update(){
    if(bLoadingPlayers == false){
        string url = "https://" + ipAdress.get() + ":8443/players";
        ofLoadURLAsync(url,"players");
        bLoadingPlayers = true;
    }
    
    std::map<int, player>::iterator onePlayer;
    for (onePlayer = mPlayers.begin(); onePlayer != mPlayers.end(); ++onePlayer)
    {
        onePlayer->second.updateAnimations();
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
                player newPlayer = player(realNr, mPositions[realNr], mColors[realNr], mSequencesPath[realNr], mBullesPath[realNr]);
                
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
float playerManager::getUserVolume(int id)
{
    std::map<int, player>::iterator onePlayer = mPlayers.find(id);
    if (onePlayer != mPlayers.end())
    {
        return onePlayer->second.getVolume();
    }
    else
        return 0;
    
    
}

//--------------------------------------------------------------
ofColor playerManager::getUserColor(int id)
{
    std::map<int, player>::iterator onePlayer = mPlayers.find(id);
    if (onePlayer != mPlayers.end()){
        return onePlayer->second.getColor();
        
    }else{
        return ofColor(127);
        
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

////--------------------------------------------------------------
//ofPoint playerManager::getHistogrammPosition(int id)
//{
//    std::map<int, player>::iterator onePlayer = mPlayers.find(id);
//    if (onePlayer != mPlayers.end())
//    {
//        return onePlayer->second.getPositionHistogram();// getVolume();
//    }
//    else
//        return ofPoint(0,0,0);
//};

////--------------------------------------------------------------
//void playerManager::draw3Signs(string _sign1, string _sign2, string _sign3){
//    
//    ofDisableDepthTest();
//    
//    std::map<int, player>::iterator onePlayer;
//    int border = 200;
//    
//    mPlayers[1].draw(mPositions[1], mBullesPos[1], true, _sign1);
//    mPlayers[2].draw(mPositions[2], mBullesPos[2], true, _sign2);
//    mPlayers[3].draw(mPositions[3], mBullesPos[3], true, _sign3);
//    
//    if(drawGui){
//        gui.draw();
//    }
//    
//}

//--------------------------------------------------------------
//void playerManager::draw(int _userId, string _textOnSign){
void playerManager::draw(){
    
    ofDisableDepthTest();
    
    std::map<int, player>::iterator onePlayer;

    for (onePlayer=mPlayers.begin(); onePlayer!=mPlayers.end(); ++onePlayer){
        onePlayer->second.draw(mBullesPos[onePlayer->second.getNumber()]);
    }
    
    if(drawGui){
        gui.draw();
    }
}

//--------------------------------------------------------------
void playerManager::startSign(int _userId, string _textOnSign, float _width){
    std::map<int, player>::iterator onePlayer = mPlayers.find(_userId);
    if (onePlayer != mPlayers.end())
    {
        onePlayer->second.startSign(_textOnSign, _width);
    }
}

//--------------------------------------------------------------
void playerManager::stopSign(int _userId){
    std::map<int, player>::iterator onePlayer = mPlayers.find(_userId);
    if (onePlayer != mPlayers.end())
    {
        return onePlayer->second.stopSign();
    }
}

//--------------------------------------------------------------
int playerManager::getRandomPlayer()
{
    std::map<int, player>::iterator onePlayer;
    
    int size = mPlayers.size();
    int rdm = int(ofRandom(0, size));
    
    onePlayer=mPlayers.begin();
    for(int i=0; i<rdm; i++)
        onePlayer++;
    
    return onePlayer->second.getNumber();
    
}


//--------------------------------------------------------------
void playerManager::urlResponse(ofHttpResponse & response){
    
    if(response.status == 200){
        if(response.request.name == "players"){
            loadPlayers(response.data);
            bLoadingPlayers = false;
        }
        if(response.request.name == "resetPlayers"){
            loadPlayers(response.data);
            bResetPlayers = false;
        }
    }else{
        ofLogError() << response.status << " " << response.error;
        
    }
}

//--------------------------------------------------------------
void playerManager::keyPressed(int key){
    
    if( key == 'h' ){
        ofLog() << "M'entends tu ???????";
        drawGui = !drawGui;
    }
    
    if(key == 's') {
        gui.saveToFile(settingsPlayers);
    }
    
    if(key == 'l') {
        gui.loadFromFile(settingsPlayers);
    }
}

