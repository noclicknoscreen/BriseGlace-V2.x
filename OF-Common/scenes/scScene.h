//
//  scScene.hpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 07/05/2018.
//
//

#pragma once

#include "ofMain.h"
#include "ofxScene.h"
#include "ofxAnimatableFloat.h"

#include "ofEvents.h"
#include "playerManager.h"

class scScene : public ofxScene {
    
public:
    void setup();
    void draw();    // Constructor
    scScene(ofEvent<void> _endSceneEvent, playerManager &_manager);
    
protected:
    ///////////// MEMBERS /////////////////////
    ofTrueTypeFont myFont24;        // Draw text
    ofEvent<void> endSceneEvent;    // Throw this event to pass the scene from
    playerManager *myPlayerManager;  // Player
    string        myTitle;
    
    ///////////// METHODS /////////////////////
    void drawCenterText(string _message, int _plusX=0, int _plusY=0);
};

