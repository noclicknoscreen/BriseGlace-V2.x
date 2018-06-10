//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "scScene.h"

class scIntro : public scScene{

public:
    // Constructor
//    scIntro(playerManager &_manager) : scScene(_manager){
//    }
	void setup();
	void update(float dt);
	void draw();
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );

    void someoneSpoke(player & _player);

private:
    timer mTimerTexte;
    void  timerTexteEnd();
    
    bool bDrawSubtitle1, bDrawSubtitle2;
    
};

