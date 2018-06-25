//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "scSelect.h"

class scSelectGame : public scSelect{
    
public:
    //    scSelectGame(playerManager &_manager) : scScene(_manager){
    //    };
    
    void setup();
    void update(float dt);
    void draw();
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
    void someoneSpoke(player & _player);
    
private:
    timer   mTimerTextSequence;
    void    timerTextSequenceEnd();
    int     mIndexSequence;
    
    timer   mTimerEraseWord;
    void  timerEraseWordEnd();
    
private:
    void  timerSignAnimationEnd();
    int   numPlayer;
    int   numMessage;
    
};

