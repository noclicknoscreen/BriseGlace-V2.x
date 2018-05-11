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

#include "ofEvents.h"
#include "playerManager.h"
#include "enigmaManager.h"

enum Scenes{ INTRO = 1, INITIALIZE, SELECT_GAME, GAME1, GAME2, GAME3, HINT, VICTORY };

class scScene : public ofxScene, ofBaseApp {
    
    
public:
    void setup();
    void draw();    // Constructor
    scScene(ofEvent<void> _endSceneEvent, playerManager &_manager);
    
    void someoneSpoke(player & _player);
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
protected:
    ///////////// MEMBERS /////////////////////
    ofTrueTypeFont myFont24;        // Draw text
    ofEvent<void> endSceneEvent;    // Throw this event to pass the scene from
    playerManager *myPlayerManager;  // Player
    string        myTitle;
    
    ///////////// METHODS /////////////////////
    void drawCenterText(string _message, int _plusX=0, int _plusY=0);
    
};

