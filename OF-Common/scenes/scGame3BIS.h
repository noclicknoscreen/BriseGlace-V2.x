//
//  scGame3BIS.h
//  theBigGame
//
//  Created by Blindsp0t on 15/05/2018.
//
//

#pragma once

#include "scGame3.h"

#define START_FORCE_FACTOR_BIS 10


class scGame3Bis : public scGame3
{
public:
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
    void update(float dt);
    void draw();
    
    // TIMERS
private:
    timer mTimerEndScene;
    void  timerEndSceneEnd();
    
};
