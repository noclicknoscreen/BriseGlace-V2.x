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
//#include "ofxGui.h"
#include "inputHandler.h"


class scGame1 : public scScene{
    
public:
    scGame1(ofEvent<void> _endSceneEvent, playerManager &_manager) : scScene(_endSceneEvent, _manager){
    };
    void setup();
    void update(float dt);
	void draw();

    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
};

