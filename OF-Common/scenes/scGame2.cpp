//
//  scGame2.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame2.h"

void scGame2::setup(){
    
    scScene::setup();
    ofLogNotice() << "Game 2 : Setup !";

    //gui
    gui.setup();
    gui.add(lightPosX.set("lightPosX", 1600, -1000, ofGetWidth()*2));
    gui.add(lightPosY.set("lightPosY", 120, -1000, 1000));
    gui.add(lightPosZ.set("lightPosZ", 0, -100, 100));
    gui.add(cubesRotationSpeed.set("cubesRotationSpeed", 5, 0.1, 20));
    
    bDrawGui=false;
    
};



void scGame2::update(float dt){
    // Cube update
    myCubeManager.update(ofPoint(lightPosX, lightPosY, lightPosZ), cubesRotationSpeed);
    // Input word (who wins)
    int id = myInputManager.update(&myCubeManager);
    
    mTimer.update(dt);
    
};

void scGame2::draw(){ //draw scene 1 here
    
//    // Draw cubes
//    ofPushStyle();
//    ofPushMatrix();
//    
//        //myCubeManager.draw();
//        
//        ofDisableLighting();
//        ofDisableDepthTest();
//        ofSetColor(255);
//        //GUI
//        if(bDrawGui)
//            gui.draw();
//    
//    ofPopStyle();
//    ofPopMatrix();
    
    // Draw Title
    scScene::drawTitle("Mes mots rient");
    scScene::drawSubTitle("Prochainement dans votre gare...");

    // Draw cubes
    myCubeManager.draw();
    // Draw floating words
    myInputManager.draw();

    // Draw players
    bigPlayerManager().draw();
    
    //GUI
    if(bDrawGui){
        gui.draw();
    }
    
};

//scene notifications
void scGame2::sceneWillAppear( ofxScene * fromScreen ){
    
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke,this,&scGame2::someoneSpoke);
    
    // Erase all words of every one
    bigPlayerManager().freshRestart();
    
    // On ne refait pas ca si on vient de l'indice
    if(fromScreen->getSceneID() != HINT){
        // Load the next enigma
        bigEnigmaManager().pickNewEnigma(IMAGE_GRID);
        
        //cubes
        myCubeManager.setup(0.75*ofGetHeight(), 7);
        //inputs
        myInputManager.setup(0.75*ofGetHeight() + 100);
        
        myInputManager.clearDuplicatesLettersHistory();
        myInputManager.setReadyForNewText();
        myInputManager.setWordToFind(utils::toUpperCase(bigEnigmaManager().getCurrentEnigma()->getSolution()));
        myInputManager.revealTirrets(&myCubeManager);
        
    }

    // -- -- -- -- --
    mTimer.startTimer(5);
    // Player manager events
    ofAddListener(mTimer.timerEnd, this, &scGame2::timerEnd);
    
};

void scGame2::timerEnd(){
    // --------------------------------
    ofxSceneManager::instance()->goToScene(INTRO);
}

//scene notifications
void scGame2::sceneWillDisappear( ofxScene * toScreen ){
    // Player manager events
    ofRemoveListener(bigPlayerManager().someoneSpoke,   this,&scGame2::someoneSpoke);
    
}

// Events callback -----------------------------------
// Speaking event
void scGame2::someoneSpoke(player & _player){
    scScene::someoneSpoke(_player);
    
    if(myInputManager.isReadyForNewText()){
        myInputManager.getNewText(_player);
    }
    
    mTimer.startTimer(45);
    
}
