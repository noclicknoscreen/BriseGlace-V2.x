//
//  scScene.hpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 07/05/2018.
//
//

#pragma once

#include "ofxSceneManager.h"

#include "ofMain.h"
#include "ofxScene.h"
#include "ofxAnimatableFloat.h"
#include "ofxTextSuite.h"

#include "ofEvents.h"
#include "playerManager.h"
#include "enigmaManager.h"

#include "utils.h"


enum Scenes{ INTRO = 1, INITIALIZE, SELECT_GAME, GAME1, GAME2, GAME3, GAME3_BIS, HINT, VICTORY };

class scScene : public ofxScene, ofBaseApp {
    
    
public:
    void setup();
    void draw();    // Constructor
    scScene(playerManager &_manager);
    
    void someoneSpoke(player & _player);
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
protected:
    ///////////// MEMBERS /////////////////////
    ofxTextBlock myText;

    playerManager *myPlayerManager;  // Player
    string        myTitle;
    
    // global timer available at anyTime
    ofxAnimatableFloat myTimer;
    void startTimer(int _seconds);
    void stopTimer();
    
//    ofEvent timerEnd;
    
};

