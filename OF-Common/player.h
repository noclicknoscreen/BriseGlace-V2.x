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
    
    void update(bool _isAvailable, string _message, string _messageToCompare, float _volume, int _number);
    void draw(ofVec2f _pos);
    
    int getVolume(){return mVolume;};
    string getLastMessage(){return mLastMessage;};
    int getNumber(){return mNumber;};
    ofColor getColor(){return mColor;};
    void setPositionHistogram(ofPoint _pos){positionHistogram = _pos;};
    ofPoint getPositionHistogram(){return positionHistogram;};
    
private:
    float mVolume;
    string mLastMessage;
    string mLastMessageToCompare;
    int mNumber;
    bool mIsAvailable;
    
    ofColor mColor;
    
    ofTrueTypeFont myFont;
    
    ofPoint positionHistogram;
    
};
