//
//  player.cpp
//  playerManager-Rough
//
//  Created by Sébastien Albert on 03/05/2018.
//
//

#include "player.h"


player::player(ofColor _color, string _characterSeqPath){
    
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
    
    // ----------
    myText.init(globalFontName, 74);
    
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
    myText.wrapTextArea(400, 300);
    
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

void player::draw(ofVec2f _pos){
    
    ofPushStyle();
    ofSetColor(mColor);
    ofFill();
    
    ofPushMatrix();
    ofTranslate(_pos);
    ofScale(0.5, 0.5);
    
//    ofNoFill();
//    ofDrawCircle(0, 0, 10);
//    ofDrawRectangle(-100, -300, 200, 300);
    
    // Draw the character
//    ofTranslate(-0.5 * mSequenceImg.getWidth(), -1 * mSequenceImg.getHeight());
    
    ofPushStyle();
    ofSetColor(255,255,255,255);
    if(mSequenceImg.isAllocated()){
        ofDisableNormalizedTexCoords();
        mSequenceImg.draw(-0.5 * mSequenceImg.getWidth(), -1 * mSequenceImg.getHeight());
        ofEnableNormalizedTexCoords();
    }
    ofPopStyle();
    
    // Draw the text
    myText.setColor(mColor.r, mColor.g, mColor.b, mColor.a);
    myText.drawCenter(0.5 * mSequenceImg.getWidth(), -1 * mSequenceImg.getHeight() - 200);
    
    ofPopMatrix();
    
    ofPopStyle();
    
}
