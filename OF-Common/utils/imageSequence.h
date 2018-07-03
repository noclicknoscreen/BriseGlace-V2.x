//
//  imageSequence.hpp
//  theBigGame
//
//  Created by Sébastien Albert on 03/07/2018.
//
//

#pragma once

#include "ofMain.h"

class imageSequence{
    // global timer available at anyTime
    
private:
    ofImage mImage;
    string  mSequencePath;
    ofImage mSequenceImg;
    int     mSequenceLen;
    int     mSequenceIdx;
    
    float   mTime;
    float   mPeriod;
    
    ofPoint mSize;
    
    void loadNewSequenceImage(float _ratio);
    
public:
    
    void update(float dt);
    void load(string _directoryPath, float _period, ofPoint _size = ofPoint::zero());
    void draw(ofPoint _pos);
    
private:
    float mRatio;
public:
    float getRatio(){return mRatio;};
    
};
