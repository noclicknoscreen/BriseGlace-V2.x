//
//  scInitialize.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scInitialize.h"

void scInitialize::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Initialisation : Setup !";
};


void scInitialize::update(float dt){ //update scene 1 here
    scScene::update(dt);
    mTimerEndScene.update(dt);
};

void scInitialize::draw(){ //draw scene 1 here
    // Draw Words
    scScene::drawTitle("Initialisation...");
    scScene::drawSpokenWord( "Il vous reste " + mTimerEndScene.toString() + " secondes pour jouer avec nous.");

    // Draw players
    bigPlayerManager().draw();
    
};

//scene notifications
void scInitialize::sceneWillAppear( ofxScene * fromScreen ){
    scScene::sceneWillAppear(fromScreen);
    
    // --
    mTimerEndScene.startTimer(20);
    // Player manager events
    ofAddListener(mTimerEndScene.timerEnd,this,&scInitialize::timerEndScene);
    
};

//scene notifications
void scInitialize::sceneWillDisappear( ofxScene * toScreen ){
    ofRemoveListener(mTimerEndScene.timerEnd,this,&scInitialize::timerEndScene);
};

// If the time is ended, we go further ---------------------------------------
void scInitialize::timerEndScene(){
    ofxSceneManager::instance()->goToScene(SELECT_GAME);
}
