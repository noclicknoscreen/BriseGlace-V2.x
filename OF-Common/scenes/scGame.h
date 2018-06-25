//
//  scGame.hpp
//  theBigGame
//
//  Created by Sébastien Albert on 06/06/2018.
//
//

#pragma once

#include "scScene.h"

// This class is made to manage common behaviours between all games
class scGame  : public scScene{
    
protected:
    timer timerSignWin;
private:
    timer timerSignHint;
    timer timerBeforeHint;
    timer timerForceWin;
private:
    void restartTimerBeforeHint();
    void restartTimerSignHint();
    void restartTimerForceWin();
    
    ///////////// SIGNS ////////////////////
protected:
    int hintUserId;
    
    // Gestion de la sequence du timer
    void loadNewSequenceImage(int _newSequenceIdx);
    string  mSequencePath;
    ofImage mSequenceImg;
    int     mSequenceIdx;
    int     mSequenceLen;
    
public:
    void setup();
    void update(float dt);
    void draw();
    
    void restartTimerSignWin();
    void stopHint();
    
    void timerBeforeHintEnd();
    void timerSignWinEnd();
    void timerSignHintEnd();
    void timerForceWinEnd();
    
    void someoneSpoke(player & _player);
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
    ///////////// CONSIGNES, TITRES ////////////////////
private:
    ofImage mCartoucheImg;
    
    ofxTextBlock    mCartoucheText;
    ofTrueTypeFont  mTitle;
    ofTrueTypeFont  mSubLine1;
    ofTrueTypeFont  mSubLine2;

protected:
    string  mGameName;
    string  mConsigne;
    
};
