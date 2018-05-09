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
    void update();
    void draw();
    
    int getLastNumber(){return mLastNumber;};
    string getLastMessage(){return mLastMessage;};
    
private:
    
    int mLastNumber;
    string mLastMessage;
    string mLastTime;
    
    ofxJSONElement mResponse;
    
    map<int, player> mPlayers;
    map<int, ofColor> mColors;
    
public:
    ofEvent<player> someoneSpoke;
    
};
