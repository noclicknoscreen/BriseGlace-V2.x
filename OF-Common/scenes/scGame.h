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
private:
    void restartTimerBeforeHint();
    void restartTimerSignHint();
    
    ///////////// SIGNS ////////////////////
protected:
    
//    bool drawWinnerSign, drawHintSign;
    int hintUserId;
    
public:
    
    void update(float dt);
    
    void restartTimerSignWin();
    
    void timerBeforeHintEnd();
    void timerSignWinEnd();
    void timerSignHintEnd();
    
    void someoneSpoke(player & _player);
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
};
