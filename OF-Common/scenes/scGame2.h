//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "scScene.h"
#include "cubeManagerMemory.h"
#include "inputHandlerMemory.h"


class scGame2 : public scScene{

public:
//    scGame2(playerManager &_manager) : scScene(_manager){
//    };
    void setup();
    void update(float dt);
	void draw();
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
  
    //cubeManager
    cubeManagerMemory myCubeManager;
    //inputManager
    inputHandlerMemory myInputManager;
    
    // Events callback
    void someoneSpoke(player & _player);
    
    //gui
    ofxPanel gui;
    ofParameter<float> lightPosX, lightPosY, lightPosZ;
    ofParameter<int> cubesRotationSpeed;
    bool bDrawGui;
    
    ///////////// TIMER, EVENTS /////////////////////
private:
    timer mTimerAfterText;

    void timerEnd();
    void timerSignWinEnd();
    void timerSignHintEnd();
    void timerAfterTextEnd();
    void readyForNewText();
    
    //

};

