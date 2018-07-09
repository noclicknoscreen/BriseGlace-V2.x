//
//  scGame.hpp
//  theBigGame
//
//  Created by Sébastien Albert on 06/06/2018.
//
//

#pragma once

#include "scScene.h"
#include "imageSequence.h"

// This class is made to manage common behaviours between all games
class scGame  : public scScene{
    
protected:
    timer mTimerSignWin;
    const float cTimerSignWin = 5.0f;

    timer mTimerBeforeHint;
    const float cTimerBeforeHint = 14.0f;
    
private:
    timer mTimerSignHint;
    const float cTimerSignHint = 4.0f;
    
    timer mTimerForceWin;
    const float cTimerForceWin = 90.0f;
    
    timer mTimerTrain;
    // TimerTrain = forceWin + signWin
    const float cTimerTrain = 100.0f;
    
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
    
    ofxTextBlock    mCartoucheTextTitle;
    ofxTextBlock    mCartoucheTextSubTi;
    
    ofTrueTypeFont  mTitle;
    ofTrueTypeFont  mSubLine1;
    ofTrueTypeFont  mSubLine2;

    int mNbHints;
    

protected:
    string  mGameName;
    string  mConsigne;
    
    // Tchou, tchou, le petit train
    imageSequence petitTrain;
    bool          mDrawPetitTrain;
    ofImage       gare;
    ofImage       depart;
    
};
