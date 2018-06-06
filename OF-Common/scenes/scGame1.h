//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "scGame.h"

#include "cubeManagerHiddenWord.h"
#include "ofxGui.h"
#include "inputHandlerHiddenWord.h"


class scGame1 : public scGame{
    
public:
//    scGame1(playerManager &_manager) : scScene(_manager){
//    };
    void setup();
    void update(float dt);
	void draw();

    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
    void keyPressed(int key);
    
    // Events callback
    void someoneSpoke(player & _player);
    void timerEnd();
    void timerSignWinEnd();
    
    //gui
    ofxPanel gui;
    ofParameterGroup             group;
    
    ofParameter<float> lightPosX, lightPosY, lightPosZ;
    ofParameter<float> orientationX, orientationY, orientationZ;
    ofParameter<float> cutOff;
    ofParameter<float> concentration;
    
    ofParameter<int> cubesRotationSpeed;
    bool bDrawGui;
    
    //cubeManager
    cubeManagerHiddenWord myCubeManager;
    
    //inputManager
    inputHandlerHiddenWord myInputManager;
    
    // Draw the overlay of hint
    bool bHintOverlay;
    
};

