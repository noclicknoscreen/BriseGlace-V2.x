//
//  player.hpp
//  playerManager-Rough
//
//  Created by Sébastien Albert on 03/05/2018.
//
//

#pragma once

#include "ofMain.h"
#include "ofxTextSuite.h"
#include "utils.h"

class player : public ofBaseApp{
    
public:
    
    player(){};
    player(ofColor _color, string _characterSeqPath, string _bullePath);
    
    void update(bool _isAvailable, string _message, string _messageToCompare, float _volume, int _number);
    void draw(ofVec2f _pos, ofPoint _bulleCorrection, bool drawSign=false, string textToDisplay="");
    
    float getVolume(){return mVolume;};
    string getLastMessage(){return mLastMessage;};
    string getLastMessageToCompare(){return mLastMessageToCompare;};
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
    ofPoint positionHistogram;
    
    // Gestion de la sequence des petits bonhommes
    void loadNewSequenceImage(int _newSequenceIdx);
    string  mSequencePath;
    ofImage mSequenceImg;
    int     mSequenceIdx;
    int     mSequenceLen;
    
    //sign
    ofImage signImage, handsImage;
    ofxTextBlock signText;
    
    // Gestion des bulles
    ofImage mBulleImg;
    string  mBullePath;
    
    //text
    ofxTextBlock myText;
    
};
