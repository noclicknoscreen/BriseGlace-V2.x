//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "scScene.h"

class scInitialize : public scScene{

public:
    scInitialize(ofEvent<void> _endSceneEvent, playerManager &_manager) : scScene(_endSceneEvent, _manager){
    };

    void setup();
    void update(float dt);
	void draw();
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
    // Timer to not wait too long
    float startTime;        // store when we start time timer
    float timerValue;
    bool bTimerReached;

};

