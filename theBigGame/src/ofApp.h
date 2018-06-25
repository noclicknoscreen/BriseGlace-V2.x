#pragma once

#include "ofMain.h"
#include "ofxAnimatableFloat.h"

#include "ofxSceneManager.h"
// Include Scenes
#include "scIntro.h"
#include "scInitialize.h"
#include "scSelectGame.h"
#include "scGame1.h"
#include "scGame2.h"
#include "scGame3.h"
#include "scGame3BIS.h"
#include "scHint.h"
#include "scVictory.h"
#include "scPartners.h"

#include "ofEvent.h"

#include "playerManager.h"

#include "enigmaManager.h"

class ofApp : public ofBaseApp{
    
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void mousePressed( int x, int y, int button );
    
    void nextSceneAuto();
    
    void windowResized(int w, int h);
    
    void goToNextScene();
    void goToPrevScene();
    
    ofxSceneManager *		sceneManager;
    
    ofTrueTypeFont myFont;
    
    ofEvent<void>        nextSceneEvent;
    
//    playerManager myPlayerManager;
//    void someoneSpoke(player & _player);
  
    ofImage background;
    bool    bFullScreen;
    void    setFullScreen();
    
};
