//
//  scVictory.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scVictory.h"

void scVictory::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Victory : Setup !";
    
};


void scVictory::update(float dt){ //update scene 1 here
    scScene::update(dt);
    mTimer.update(dt);
};

void scVictory::draw(){ //draw scene 1 here
    
    ofPushStyle();
    
        // Style setup
        ofSetColor(ofColor::black);
        scScene::drawTitle("Gagné !");
        scScene::drawSpokenWord("Nouveau jeu dans " + mTimer.toString() + " secondes.");
    
    ofPopStyle();
    
};

//scene notifications
void scVictory::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    // --
    mTimer.startTimer(25);
    // Player manager events
    ofAddListener(mTimer.timerEnd,this,&scVictory::timerEnd);
};

//scene notifications
void scVictory::sceneWillDisappear( ofxScene * toScreen ){
    ofRemoveListener(mTimer.timerEnd,this,&scVictory::timerEnd);
}

// If the time is ended, we go further ---------------------------------------
void scVictory::timerEnd(){
    ofxSceneManager::instance()->goToScene(INTRO);
}

