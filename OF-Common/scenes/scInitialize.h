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
//    scInitialize(playerManager &_manager) : scScene(_manager){
//    };

    void setup();
    void update(float dt);
	void draw();
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
    // TIMERS
private:
    timer mTimerEndScene;
    void  timerEndScene();


};

