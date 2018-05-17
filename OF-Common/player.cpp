//
//  player.cpp
//  playerManager-Rough
//
//  Created by Sébastien Albert on 03/05/2018.
//
//

#include "player.h"

#define internalBulleSize ofPoint(365, 172)
#define internalBullePos ofPoint(15,19)

player::player(ofColor _color, string _characterSeqPath, string _bullePath){
    
    mColor = _color;
    
    // Check the path of the sequence and do some coffee
    ofDirectory seq(_characterSeqPath);
    if(!seq.exists()){
        ofLogError() << "Sequence Path [" << _characterSeqPath << "] does not exist.";
    }else if(!seq.isDirectory()){
        ofLogError() << "Sequence Path [" << _characterSeqPath << "] is not directory.";
    }else{
        seq.allowExt("png");
        mSequenceLen = seq.listDir();
        mSequencePath = _characterSeqPath;
        
        ofLogNotice() << "Sequence Path [" << mSequencePath << "] seems good :) and is [" << mSequenceLen<< "] images long";
        
        // This -1 value force the first load
        mSequenceIdx = -1;
        loadNewSequenceImage(0);
        
    }
    
    // Check the path of the bulle
    ofFile _bulle(_bullePath);
    if(!_bulle.exists()){
        ofLogError() << "Bulle Path [" << _bullePath << "] does not exist.";
        mBullePath = "void.jpg";
    }else if(_bulle.getExtension() != "png" && _bulle.getExtension() != "jpg" && _bulle.getExtension() != "jpeg"){
        ofLogError() << "Bulle Path [" << _bullePath << "] is not image.";
        mBullePath = "void.jpg";
    }else{
        mBullePath = _bullePath;
        ofLogNotice() << "Bulle Path [" << _bullePath << "] seems good :)";
    }
    mBulleImg.load(mBullePath);
    
    // ----------
    myText.init(globalFontName, globalFontSizeBig);
    
}

void player::update(bool _isAvailable, string _message, string _messageToCompare, float _volume, int _number){
    
    mVolume = 0.5*mVolume + 0.5*ofMap(_volume, 0.00001, .01, 0, 1, true);
    
    mLastMessage = _message;
    mLastMessageToCompare = _messageToCompare;
    mIsAvailable = _isAvailable;
    mNumber = _number;
    
    // We re-map the volume between the end and the start of a sequence
    loadNewSequenceImage((int)ofMap(mVolume, 0, 1, 0, mSequenceLen - 1, true));
    
    // Set the text
    
    myText.setText(utils::toUpperCase(mLastMessage));
    myText.wrapTextArea(0.9 * internalBulleSize.x, 0.9 * internalBulleSize.y);
    myText.setColor(0, 0, 0, 255);
    
}

void player::loadNewSequenceImage(int _newSequenceIdx){
    
    if(_newSequenceIdx>=0 && _newSequenceIdx<=(mSequenceLen - 1) && _newSequenceIdx != mSequenceIdx){
        
        mSequenceIdx = _newSequenceIdx;
        string imgPath = mSequencePath+"/"+mSequencePath+"_"+ ofToString(mSequenceIdx,5,'0') +".png";
        //        ofLogNotice() << "Image path = " << imgPath;
        if(ofFile(imgPath).exists()){
            mSequenceImg.load(imgPath);
        }else{
            ofLogError() << "Image path [" + imgPath + "] not exists.";
            mSequenceImg.load("void.jpg");
        }
        
    }else{
        //        ofLogNotice() << "Something happened with the sequence index : " << _newSequenceIdx;
    }
    
}

void player::draw(ofVec2f _pos, ofPoint _bulleCorrection){
    
    setPositionHistogram(_pos);
    
    ofPushStyle();
    ofSetColor(mColor);
    ofFill();
    
    ofPushMatrix();
    ofTranslate(_pos);
    
    // Draw the character
    ofPushStyle();
    
    
    ofPushMatrix();
    ofTranslate(-0.5 * mSequenceImg.getWidth() + _bulleCorrection.x, -1 * mSequenceImg.getHeight() - 200  + _bulleCorrection.y);
    //            ofScale(0.75, 0.75);
    
    if(mBulleImg.isAllocated()){
        ofFill();
        ofSetColor(255,255,255,255);
        ofDisableNormalizedTexCoords();
        mBulleImg.draw(0, 0);
        ofEnableNormalizedTexCoords();
    }
    
    // Draw the text
    ofSetColor(mColor);
    ofNoFill();
    //            ofDrawRectangle(internalBullePos.x, internalBullePos.y, internalBulleSize.x, internalBulleSize.y);
    
    
    ofPoint whereTheTextIs(internalBullePos.x + 0.5*internalBulleSize.x, internalBullePos.y + 0.15*myText.getHeight(), 10);
    //            ofDrawCircle(whereTheTextIs.x , whereTheTextIs.y, 10);
    myText.drawCenter(whereTheTextIs.x , whereTheTextIs.y);
    
    ofPopMatrix();
    
    ofPushMatrix();
    ofScale(0.5, 0.5);
    
    //            ofNoFill();
    //            ofDrawCircle(0, 0, 10);
    //            ofDrawRectangle(-100, -300, 200, 300);
    
    if(mSequenceImg.isAllocated()){
        ofSetColor(255,255,255,255);
        
        ofDisableNormalizedTexCoords();
        mSequenceImg.draw(-0.5 * mSequenceImg.getWidth(), -1 * mSequenceImg.getHeight());
        ofEnableNormalizedTexCoords();
    }
    ofPopMatrix();
    
    
    ofPopStyle();
    
    
    ofPopMatrix();
    
    ofPopStyle();
    
}
