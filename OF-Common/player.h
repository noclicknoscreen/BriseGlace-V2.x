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
#include "ofxAnimatableFloat.h"
#include "utils.h"

class player : public ofBaseApp{
    
public:
    
    player(){};
    player(ofPoint _position, ofColor _color, string _characterSeqPath, string _bullePath);
    
    void update(bool _isAvailable, string _message, string _messageToCompare, float _volume, int _number);
    void updateAnimations();
//    void draw(ofVec2f _pos, ofPoint _bulleCorrection);
    void draw(ofPoint _bulleCorrection);
    
    float getVolume(){return mVolume;};
    string getLastMessage(){return mLastMessage;};
    string getLastMessageToCompare(){return mLastMessageToCompare;};
    int getNumber(){return mNumber;};
    ofColor getColor(){return mColor;};
//    void setPositionHistogram(ofPoint _pos){positionHistogram = _pos;};
    ofPoint getPosition(){return mPosition;};
    
    void startSign(string _textOnSign="");
    void stopSign();
    
private:
    float mVolume;
    string mLastMessage;
    string mLastMessageToCompare;
    int mNumber;
    bool mIsAvailable;
    
    ofColor mColor;
    ofPoint mPosition;
//    ofPoint positionHistogram;
    
    ofPoint              mSignUpAndDown;
    ofxAnimatableFloat   mSignAnimation;
    string               mSignText;
    bool                 mSignDraw;
    
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
