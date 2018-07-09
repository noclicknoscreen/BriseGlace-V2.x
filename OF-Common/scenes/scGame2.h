//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "scGame.h"
#include "cubeManagerMemory.h"
#include "inputHandlerMemory.h"


class scGame2 : public scGame{

public:
//    scGame2(playerManager &_manager) : scScene(_manager){
//    };
    void setup();
    void update(float dt);
	void draw();
    void keyPressed(int key);
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
  
    //cubeManager
    cubeManagerMemory myCubeManager;
    //inputManager
    inputHandlerMemory myInputManager;
    
    // Events callback
    void someoneSpoke(player & _player);
    void timerSignWinEnd();
    
    //gui
    ofxPanel gui;
    ofParameterGroup             group;
    
    ofParameter<float> lightPosX, lightPosY, lightPosZ;
    ofParameter<float> orientationX, orientationY, orientationZ;
    ofParameter<float> cutOff;
    ofParameter<float> concentration;
    ofParameter<float> cubesRotationSpeed;
    ofParameter<float> alphaDecay;
    
    bool bDrawGui;
    
    ///////////// TIMER, EVENTS /////////////////////
private:
    timer mTimerAfterText;

    void timerAfterTextEnd();
    void readyForNewText();
    
    ofTrueTypeFont  mAuthorDraw;
    
    
};

