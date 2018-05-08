//
//  player.hpp
//  playerManager-Rough
//
//  Created by Sébastien Albert on 03/05/2018.
//
//

#pragma once

#include "ofMain.h"

class player : public ofBaseApp{
    
public:
    
    player(ofColor _color);
    
    void update(bool _isAvailable, string _message, float _volume);
    void draw(ofVec2f _pos);
    
    int getVolume(){return mVolume;};
    string getLastMessage(){return mLastMessage;};
    
private:
    float mVolume;
    string mLastMessage;
    bool mIsAvailable;
    
    ofColor mColor;
    
    ofTrueTypeFont myFont;
    
};
