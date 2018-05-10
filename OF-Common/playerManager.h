//
//  playerManager.hpp
//  playerManager-Rough
//
//  Created by Sébastien Albert on 03/05/2018.
//
//

#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "player.h"

class playerManager : public ofBaseApp{
    
public:
//    void setup(ofEvent<player> _someoneSpoke);
    void setup();
    void freshRestart(); // Reset messages for fresh restart
    void update();
    void draw();
    
    int getLastNumber(){return mLastNumber;};
    string getLastMessage(){return mLastMessage;};
    
    void urlResponse(ofHttpResponse & response);
    
private:
    
    int mLastNumber;
    string mLastMessage;
    string mLastTime;
    
    ofxJSONElement mResponse;
    
    ofHttpRequest request;
    
    map<int, player> mPlayers;
    map<int, ofColor> mColors;
    
    bool bLoadingPlayers = false;
    void loadPlayers(ofBuffer _datas);
    
public:
    ofEvent<player> someoneSpoke;
    
};
