//
//  player.cpp
//  playerManager-Rough
//
//  Created by Sébastien Albert on 03/05/2018.
//
//

#include "player.h"


player::player(ofColor _color){
    myFont.load("Folktale.ttf", 16, true, true);
    mColor = _color;
}

void player::update(bool _isAvailable, string _message, string _messageToCompare, float _volume, int _number){
    mVolume = 0.5*mVolume + 0.5*ofMap(_volume, 0.0001, .001, 0, 1, true);
    mLastMessage = _message;
    mLastMessageToCompare = _messageToCompare;
    mIsAvailable = _isAvailable;
    mNumber = _number;
}

void player::draw(ofVec2f _pos){
    
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(_pos);
    
    ofSetColor(mColor);
    if(mIsAvailable == true){
        ofFill();
    }else{
        ofNoFill();
    }
    
    int maxSize = 100;
    int realSize = ofMap(mVolume, 0, 1, 0, maxSize, true);
    int nbRectangles = 10;
    int sizes[] = {20, 12, 32, 48, 60, 80, 56, 8, 12, 20};
    
    ofPushMatrix();
    ofTranslate(-0.5 * maxSize, 0);
    for(int idxRectangle=0; idxRectangle < nbRectangles; idxRectangle++){
        ofDrawRectangle(((float)idxRectangle / (float)nbRectangles) * maxSize, 0, maxSize/nbRectangles, -1.0 * ofMap(mVolume, 0, 1, 0, sizes[idxRectangle], true));
    }
    ofPopMatrix();
    
    
    ofRectangle bounds = myFont.getStringBoundingBox(mLastMessage, 0, 0);
    myFont.drawString(mLastMessage, -0.5 * bounds.width, -0.5 * bounds.height);
    
    ofPopStyle();
    ofPopMatrix();
    
}
