//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "scScene.h"

#include "cubeManager.h"
#include "ofxGui.h"
#include "inputHandler.h"


class scGame1 : public scScene{
    
public:
    scGame1(playerManager &_manager) : scScene(_manager){
    };
    void setup();
    void update(float dt);
	void draw();

    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
    void keyPressed(int key);
    
    void someoneSpoke(player & _player);
    //string toUpperCase(string str);
    
    //gui
    ofxPanel gui;
    ofParameter<float> lightPosX, lightPosY, lightPosZ;
    ofParameter<int> cubesRotationSpeed;
    
    //cubeManager
    cubeManager myCubeManager;
    
    //inputManager
    inputHandler myInputManager;
    
};

