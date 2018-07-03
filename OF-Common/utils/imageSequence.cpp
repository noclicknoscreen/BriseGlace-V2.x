//
//  imageSequence.cpp
//  theBigGame
//
//  Created by Sébastien Albert on 03/07/2018.
//
//

#include "imageSequence.h"

void imageSequence::load(string _directoryPath, float _period, ofPoint _size){
    
    // Check the path of the sequence and do some coffee
    ofDirectory seq(_directoryPath);
    
    if(_period >= 0.0f){
        mPeriod = _period;
    }else{
        ofLogError() << "Period first set to Zero, forced to Value 1.Of";
        mPeriod = 1.0f;
    }
    
    mSize = _size;
    mRatio = 0.0f;
    
    if(!seq.exists()){
        ofLogError() << "Sequence Path [" << _directoryPath << "] does not exist.";
    }else if(!seq.isDirectory()){
        ofLogError() << "Sequence Path [" << _directoryPath << "] is not directory.";
    }else{
        seq.allowExt("png");
        mSequenceLen = seq.listDir();
        mSequencePath = _directoryPath;
        
        ofLogNotice() << "Sequence Path [" << mSequencePath << "] seems good :) and is [" << mSequenceLen<< "] images long";
        
        // This -1 value force the first load
        loadNewSequenceImage(0);
        
    }
    
}


void imageSequence::update(float dt){
    
    mTime += dt;
    mTime = fmod(mTime, mPeriod);
    mRatio = mTime / mPeriod;
    
//    ofLogNotice() << "Time elapsed in Sequence : " << mSequencePath << " : " << ofToString(mTime) << " ratio is : " << ofToString(mRatio);
    
    loadNewSequenceImage(mRatio);
    
}

void imageSequence::loadNewSequenceImage(float _ratio){
    
    int newSequenceIdx = (int)ofMap(_ratio, 0, 1, 0, mSequenceLen - 1, true);
    
    if(newSequenceIdx>=0 && newSequenceIdx<=(mSequenceLen - 1) && newSequenceIdx != mSequenceIdx){
        
        string imgPath = mSequencePath+"/"+mSequencePath+"_"+ ofToString(newSequenceIdx,5,'0') +".png";
        //        ofLogNotice() << "Image path = " << imgPath;
        if(ofFile(imgPath).exists()){
            mSequenceIdx = newSequenceIdx;
            mSequenceImg.load(imgPath);
        }else{
            ofLogError() << "Image path [" + imgPath + "] not exists.";
            mSequenceImg.load("void.jpg");
        }
        
        if(mSize != ofPoint::zero()){
            mSequenceImg.resize(mSize.x, mSize.y);
        }
        
    }else{
        //        ofLogNotice() << "Something happened with the sequence index : " << _newSequenceIdx;
    }
    
}

void imageSequence::draw(ofPoint _pos){
    
    if(mSequenceImg.isAllocated()){
        ofSetColor(255,255,255,255);
        
        ofDisableNormalizedTexCoords();
        mSequenceImg.draw(_pos.x - 0.5 * mSequenceImg.getWidth(), _pos.y - 0.5 * mSequenceImg.getHeight());
        ofEnableNormalizedTexCoords();
    }
    
}

