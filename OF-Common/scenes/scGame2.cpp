//
//  scGame2.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame2.h"

//=======================================================================
//
//======= MES MOTS RIENT ================================================
//
//=======================================================================

void scGame2::setup(){
    
    scGame::setup();
    ofLogNotice() << "Game 2 : Setup !";

    //gui
    group.setName("Game2");
    group.add(lightPosX.set("lightPosX", 1600, -3000, 3000));
    group.add(lightPosY.set("lightPosY", 120, -3000, 3000));
    group.add(lightPosZ.set("lightPosZ", 0, -3000, 3000));
    
    group.add(orientationX.set("orientationX", 0, 0, 360));
    group.add(orientationY.set("orientationY", 0, 0, 360));
    group.add(orientationZ.set("orientationZ", 0, 0, 360));
    
    group.add(cutOff.set("cutOff", 0, 0, 180));
    group.add(concentration.set("concentration", 0, 0, 180));
    
    group.add(cubesRotationSpeed.set("cubesRotationSpeed", 5, 0.1, 20));
    
    gui.setup(group);
    gui.loadFromFile(settingsFileNameGame2);
    
    bDrawGui=false;
    
};



void scGame2::update(float dt){
    
    scGame::update(dt);
    
    // Cube update
    myCubeManager.update(ofPoint(lightPosX, lightPosY, lightPosZ), ofPoint(orientationX, orientationY, orientationZ), cutOff, concentration, cubesRotationSpeed);
    
    
    if(bigPlayerManager().getWinnerUserId() == 0){
        // Input word (who wins)
        myInputManager.update(&myCubeManager);
    }

    // update a timer for post animation
    mTimerAfterText.update(dt);
    
};

void scGame2::draw(){ //draw scene 1 here

    //GUI
    if(bDrawGui){
        ofDisableLighting();
        gui.draw();
    }
    
    // Draw Title
    scScene::drawTitle("Mes mots rient", ofColor::black, ofPoint(0.17 * ofGetWidth(), 0.15 * ofGetHeight()));
    scScene::drawSubTitle("Trouve le mot grâce à l'image", ofColor::black, ofPoint(0.17 * ofGetWidth(), 0.15 * ofGetHeight()));
    scScene::drawSubTitle("cachée derrière ces lettres", ofColor::black, ofPoint(0.17 * ofGetWidth(), 0.20 * ofGetHeight()));

    // Draw cubes
    myCubeManager.draw();
    
    // Draw floating words
    myInputManager.draw();

    // Draw players
//    if(drawWinnerSign)
//        bigPlayerManager().draw(bigPlayerManager().getWinnerUserId(), "c'est gagné");
//    else if(drawHintSign)
//        bigPlayerManager().draw(hintUserId, "veux-tu un indice ?");
//    else
        bigPlayerManager().draw();    // Draw players
    
};

//scene notifications
void scGame2::sceneWillAppear( ofxScene * fromScreen ){
    
    // reset our scene when we appear
    scGame::sceneWillAppear(fromScreen);
    // Player manager events
    ofAddListener(timerSignWin.timerEnd,    this,&scGame2::timerSignWinEnd);
    
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke,  this,&scGame2::someoneSpoke);
    ofAddListener(mTimerAfterText.timerEnd,         this,&scGame2::timerAfterTextEnd);
    ofAddListener(myInputManager.readyForNewText,   this,&scGame2::readyForNewText);
    
//    // Erase all words of every one
//    bigPlayerManager().freshRestart();
    
    // On ne refait pas ca si on vient de l'indice
    if(fromScreen->getSceneID() != HINT){
        
        // Reset winner
        bigPlayerManager().setWinnerUserId(0);

        // Load the next enigma
        bigEnigmaManager().pickNewEnigma(IMAGE_GRID);
        
        //cubes
        myCubeManager.setup(ofPoint(0.2*ofGetWidth(), 0.33*ofGetHeight(), -300), 7, 150);
        //inputs
        myInputManager.setup(ofPoint(0.67 * ofGetWidth(), 0.6 * ofGetHeight()));
        
        myInputManager.clearDuplicatesLettersHistory();
        myInputManager.setReadyForNewText();
        myInputManager.setMysteryString(myCubeManager.getContent());
        myInputManager.revealTirrets(&myCubeManager);
        
    }

};

//scene notifications
void scGame2::sceneWillDisappear( ofxScene * toScreen ){
    scGame::sceneWillDisappear(toScreen);
    // Disable timer events
    ofRemoveListener(timerSignWin.timerEnd,     this,&scGame2::timerSignWinEnd);
    
    // Player manager events
    ofRemoveListener(bigPlayerManager().someoneSpoke,   this,&scGame2::someoneSpoke);
    ofRemoveListener(mTimerAfterText.timerEnd,          this,&scGame2::timerAfterTextEnd);
    ofRemoveListener(myInputManager.readyForNewText,    this,&scGame2::readyForNewText);
}

//--------------------------------------------------------------
void scGame2::keyPressed(int key){
    
    if(key=='l')
        myCubeManager.rotateToLetter(0);
    if(key=='w')
        myCubeManager.rotateToWood(0);
    if(key=='W')
        myCubeManager.rotateToWhite(0);
    if(key == 's') {
        gui.saveToFile(settingsFileNameGame2);
    }
    if(key == 'l') {
        gui.loadFromFile(settingsFileNameGame2);
    }
    if(key==' ' ){
        bDrawGui = !bDrawGui;
    }
}

// Events callback -----------------------------------
// Speaking event
void scGame2::someoneSpoke(player & _player){
    scGame::someoneSpoke(_player);
    
    if(myInputManager.isReadyForNewText()){
        myInputManager.getNewText(_player);
    }
    
    int compare = ofStringTimesInString(utils::toUpperCase(_player.getLastMessage()), utils::toUpperCase(bigEnigmaManager().getCurrentEnigma()->getSolution()));
    if(compare > 0)
    {
        ofLogNotice() << "We have a winner [" << _player.getLastMessage() << "] = [" << bigEnigmaManager().getCurrentEnigma()->getSolution() << "], compare = " << compare;
        bigPlayerManager().setWinnerUserId(_player.getNumber());
        myCubeManager.rotateAllToWhite();
        bigPlayerManager().startSign(_player.getNumber(), "C'est gagné !");
        restartTimerSignWin();
        stopHint();
        
    }else{
        ofLogNotice() << "Final comparaison failed [" << _player.getLastMessage() << "] different from [" << bigEnigmaManager().getCurrentEnigma()->getSolution() << "], compare = " << compare;
    }
    
}
// VICTORY Event , go to scene you prefer
void scGame2::timerSignWinEnd(){
    scGame::timerSignWinEnd();
    ofxSceneManager::instance()->goToScene(VICTORY);
}

void scGame2::timerAfterTextEnd(){
    
    ofLogNotice() << "fin du timer after text, roll back cubes";
    // --------------------------------
    myCubeManager.rotateAllToLetter();
    mTimerAfterText.stop();
}

void scGame2::readyForNewText(){
    
    ofLogNotice() << "Ready for a new entry, roll back in one second";
    // --------------------------------
    mTimerAfterText.startTimer(1);
}
