//
//  playerManager.hpp
//  playerManager-Rough
//
//  Created by Sébastien Albert on 03/05/2018.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxJSON.h"
#include "player.h"

class playerManager : public ofBaseApp{
    
public:
//    void setup(ofEvent<player> _someoneSpoke);
    void setup();
    void freshRestart(); // Reset messages for fresh restart
    void update();
    void draw(int _userId = 0, string _textOnSign="");
    void draw3Signs(string _sign1, string _sign2, string _sign3);
    
    void keyPressed(int key);
    
    int getLastNumber(){return mLastNumber;};
    string getLastMessage(){return mLastMessage;};
    
    float getSumVolume();
    float getAverageVolume();
    float getUserVolume(int id);
    ofPoint getHistogrammPosition(int id);
    
    
    int getNumberOfPlayers(){return mPlayers.size();}
    int getRandomPlayer();
    
    ofColor getUserColor(int _userId);
    
    void urlResponse(ofHttpResponse & response);
    
private:
    
    int mLastNumber;
    string mLastMessage;
    string mLastTime;
    
    ofxJSONElement mResponse;
    
    ofHttpRequest request;
    
    map<int, player> mPlayers;
    
    map<int, ofColor> mColors;
    map<int, string> mSequencesPath;
    map<int, string> mBullesPath;
    map<int, ofPoint> mBullesPos;
    map<int, ofPoint> mPositions;
    
    bool bLoadingPlayers    = false;
    bool bResetPlayers      = false;
    void loadPlayers(ofBuffer _datas);
    
    // GUI, settings
    //parameters
    ofxPanel                     gui;
    bool                         drawGui;
    ofParameter<ofColor>         player1, player2, player3, player4;
    ofParameter<string>          ipAdress;
    
public:
    ofEvent<player> someoneSpoke;
    
    // SINGLETON //
public:
    static playerManager& get(){
        static playerManager myPlayerManager;
        return myPlayerManager;
    }
    
// Winner system
private:
    int mWinnerUserId;
public:
    void setWinnerUserId(int _id){mWinnerUserId = _id;};
    int getWinnerUserId(){return mWinnerUserId;};
    
};

inline playerManager& bigPlayerManager()
{
    return playerManager::get();
}
