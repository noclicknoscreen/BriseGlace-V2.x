//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "scScene.h"
#include "indice.h"


class scHint : public scScene{

public:
//    scHint(playerManager &_manager) : scScene(_manager){
//    };
    void setup();
    void update(float dt);
	void draw();
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
    indice myIndice;
    
    float timer;

    void someoneSpoke(player & _player);
    
};

