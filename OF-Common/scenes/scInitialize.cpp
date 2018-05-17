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
    mTimer.update(dt);
};

void scInitialize::draw(){ //draw scene 1 here
    // Draw Words
    scScene::drawTitle("Initialisation...");
    scScene::drawSpokenWord( "Il vous reste " + mTimer.toString() + " secondes pour jouer avec nous.");

    // Draw players
    bigPlayerManager().draw();
    
};

//scene notifications
void scInitialize::sceneWillAppear( ofxScene * fromScreen ){
    scScene::sceneWillAppear(fromScreen);
    
    // --
    mTimer.startTimer(20);
    // Player manager events
    ofAddListener(mTimer.timerEnd,this,&scInitialize::timerEnd);
    
};

//scene notifications
void scInitialize::sceneWillDisappear( ofxScene * toScreen ){
    ofRemoveListener(mTimer.timerEnd,this,&scInitialize::timerEnd);
};

// If the time is ended, we go further ---------------------------------------
void scInitialize::timerEnd(){
    ofxSceneManager::instance()->goToScene(SELECT_GAME);
}
