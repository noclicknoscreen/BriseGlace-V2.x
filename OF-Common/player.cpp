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

player::player(int _number, ofPoint _position, ofColor _color, string _characterSeqPath, string _bullePath){
    
    mColor = _color;
    mIsAvailable = false;
    
    mPosition = _position;
    mNumber   = _number;
    
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
    signText.init(globalFontName, globalFontSizeBig);
    
    //load sign and hands
    signImage.load("Pancarte/Pancarte-Ombres.png");
    handsImage.load("Pancarte/Mains_seules.png");
    
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

void player::updateAnimations(){
    // Sign animation
    float dt = 1.0f / (float)ofGetFrameRate();
    mSignAnimation.update(dt);
    mSignUpAndDown.x = 0;
    mSignUpAndDown.y = ofMap(mSignAnimation.getCurrentValue(), 0, 1, 200.0f, -350.0f);
    
    mSignScale.x = ofMap(mSignAnimation.getCurrentValue(), 0, 1, 0.75f, 1.0f);
    mSignScale.y = ofMap(mSignAnimation.getCurrentValue(), 0, 1, 0.25f, 1.0f);
    
    
//    ofLogNotice() << "Player n° " << mNumber << " : Timer sign value = " << mSignAnimation.getCurrentValue();
    if(mSignAnimation.getCurrentValue() <= 0.0f){
        mSignDraw = false;
    }else{
        mSignDraw = true;
    }
    
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

void player::draw(ofPoint _bulleCorrection){
    
    ofPushStyle();
    ofSetColor(mColor);
    ofFill();
    
    ofPushMatrix();
    ofTranslate(mPosition);
    
    // Draw the character
    ofPushStyle();
    
    // DRAW MOT ////////////////////////////////////////////////////////////////
    ofPushMatrix();
    ofPoint realPosBulle(-0.5 * mSequenceImg.getWidth() + _bulleCorrection.x, -1 * mSequenceImg.getHeight() - 200  + _bulleCorrection.y);
    ofTranslate(realPosBulle);
    //            ofScale(0.75, 0.75);
    
    if(mIsAvailable){
    
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
        
        
        // Little trick to always be into the frame
        ofPoint whereTheTextIs(internalBullePos.x + 0.5*internalBulleSize.x, internalBullePos.y - 0.5*internalBulleSize.y + 0.5 * mBulleImg.getHeight() - 0.25 * myText.getHeight());
        myText.drawCenter(whereTheTextIs.x , whereTheTextIs.y);
        
    }
    ofPopMatrix();
    //////////////////////////////////////////////////////////////////
    
    // DRAW BONHOMME ////////////////////////////////////////////////////////////////
    ofPushMatrix();
    ofScale(0.5, 0.5);

    if(mSequenceImg.isAllocated()){
        ofSetColor(255,255,255,255);
        
        ofDisableNormalizedTexCoords();
        mSequenceImg.draw(-0.5 * mSequenceImg.getWidth(), -1 * mSequenceImg.getHeight());
        ofEnableNormalizedTexCoords();
    }
    
    
    // DRAW SIGN IF NEEDED /////////////////////////////////////////////////////////////
    if(mSignDraw)
    {
        signText.setText(utils::toUpperCase(mSignText));
        signText.wrapTextX(mSignRelativeWidth*signImage.getWidth());
        
        ofDisableNormalizedTexCoords();
        
        ofPushMatrix();
        ofScale(mSignScale);
        ofTranslate(mSignUpAndDown);
        ofTranslate(-0.5 * signImage.getWidth(), -0.5 * signImage.getHeight() + abs(cos(ofGetFrameNum()/75.0))*50);
        signImage.draw(0,0);
        
        //debug
        /*
         ofNoFill();
         ofSetColor(ofColor::red);
         ofDrawRectangle(0, 0, signImage.getWidth(), signImage.getHeight());
         ofDrawCircle(signImage.getWidth()/2, signImage.getHeight()/2, 10);
         ofFill();
         */
        
        //text
        ofPushMatrix();
        ofTranslate(signImage.getWidth()/2, signImage.getHeight()/2 - signText.getHeight()/2 - 30);
        ofRotate(-10, 0, 0, 1); //tilt the text a bit
        signText.setColor(0, 0, 0, 255);
        signText.drawCenter(0,0);
        ofPopMatrix();//text
        
        //draw hands over the text
        ofSetColor(255, 255, 255, 255);
        handsImage.draw(0,0);
        
        ofPopMatrix();//signImage
        ofEnableNormalizedTexCoords();
        
        
    }

    //////////////////////////////////////////////////////////////////
    ofPopMatrix();
    ofPopStyle();
    
    
    ofPopMatrix();
    
    ofPopStyle();
    
}

void player::startSign(string _text, float _width){
    // Sign animation
    mSignAnimation.reset(0.0f);
    mSignAnimation.setCurve(QUADRATIC_EASE_OUT);
    mSignAnimation.setRepeatType(PLAY_ONCE);
    mSignAnimation.setDuration(0.5);
    mSignAnimation.animateTo(1.0f);
    
    mSignText = _text;
    mSignRelativeWidth = _width;
    
}

void player::stopSign(){
    if(mSignDraw == true){
        // Sign animation
        mSignAnimation.reset(1.0f);
        mSignAnimation.setCurve(QUADRATIC_EASE_OUT);
        mSignAnimation.setRepeatType(PLAY_ONCE);
        mSignAnimation.setDuration(0.5);
        mSignAnimation.animateTo(0.0f);
    }
}
