//
//  scScene.hpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 07/05/2018.
//
//

#pragma once

#include "ofMain.h"
#include "ofxScene.h"
#include "ofxAnimatableFloat.h"

#include "ofEvents.h"

class scScene : public ofxScene {
    
public:
    void setup(){
        myFont24.load("Folktale.ttf", 24, true, true);
    }
    // Constructor
    scScene(ofEvent<void> _event){
        endSceneEvent = _event;
    }
    
protected:
    // Draw text
    ofTrueTypeFont myFont24;
    // Throw this event to pass the scene from
    ofEvent<void> endSceneEvent;
};

