//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "scScene.h"
//#include "indice.h"
#include "cubeManagerHint.h"
#include "cubeManagerMemory.h"



class scHint : public scScene{

public:
//    scHint(playerManager &_manager) : scScene(_manager){
//    };
    void setup();
    void update(float dt);
	void draw();
    void keyPressed(int key);
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
//    indice myIndice;
    cubeManagerHint myCubeManager;
    
    //gui
    ofxPanel gui;
    ofParameterGroup             group;
    
    ofParameter<float> lightPosX, lightPosY, lightPosZ;
    ofParameter<float> orientationX, orientationY, orientationZ;
    ofParameter<float> cutOff;
    ofParameter<float> concentration;
    ofParameter<float> cubesRotationSpeed;
    ofParameter<float> waitTimeBeforeRoll;
    ofParameter<float> timeInBetweenRolls;
    
    bool bDrawGui;
    
    void someoneSpoke(player & _player);
    
    ofxScene* from;

private:
    timer mTimerEndScene;
    void  timerEndScene();
    
    timer mTimerStartRoll;
    void  timerStartRollEnd();
    
    timer mTimerBeforeRoll;
    void  timerBeforeRollEnd();
    
    int   currentCube;
};

