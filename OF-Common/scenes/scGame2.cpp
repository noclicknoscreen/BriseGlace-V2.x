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
    group.add(alphaDecay.set("alphaDecay", 0.01, 0.01, 0.03));
    
    gui.setup(group);
    gui.loadFromFile(settingsFileNameGame2);
    
    bDrawGui=false;
    
    mGameName = "MES MOTS RIENT";
    mConsigne = "UN MOT SE CACHE PARMI CES LETTRES. PARLEZ POUR VOIR !";
    
    // Draw author
    mAuthorDraw.load(globalFontName, 8);

    
};



void scGame2::update(float dt){
    
    scGame::update(dt);
    
    // Cube update
    myCubeManager.update(ofPoint(lightPosX, lightPosY, lightPosZ), ofPoint(orientationX, orientationY, orientationZ), cutOff, concentration, cubesRotationSpeed);
    
    
    if(bigPlayerManager().getWinnerUserId() == 0){
        // Input word (who wins)
        myInputManager.update(&myCubeManager, alphaDecay);
    }

    // update a timer for post animation
    mTimerAfterText.update(dt);
    
    if(myInputManager.isReadyForNewText()){
        mTimerBeforeHint.resume();
    }else{
        mTimerBeforeHint.pause();
        // Stop display Hint
        stopHint();
//        bigPlayerManager().stopSign(hintUserId);
    }
    
};

void scGame2::draw(){ //draw scene 1 here

    //GUI
    if(bDrawGui){
        ofDisableLighting();
        gui.draw();
    }
    
    // Draw author
    ofPushStyle();
    
    ofEnableAlphaBlending();
    ofSetColor(ofColor::black, 200);
    
    ofPushMatrix();
    ofTranslate(150, 0.77 * ofGetHeight() - 38);
    ofRotateZ(-90);
    
    mAuthorDraw.drawString(bigEnigmaManager().getCurrentEnigma()->getAuteurMot(), 0, 0);
    
    ofPopStyle();
    ofPopMatrix();
    
    // Draw mother of draw
    scGame::draw();

    // Draw cubes
    myCubeManager.draw();
    
    // Draw floating words
    myInputManager.draw();

    // Draw players
    bigPlayerManager().draw();
    
};

//scene notifications
void scGame2::sceneWillAppear( ofxScene * fromScreen ){
    
    // reset our scene when we appear
    scGame::sceneWillAppear(fromScreen);
    // Player manager events
    ofAddListener(mTimerSignWin.timerEnd,    this,&scGame2::timerSignWinEnd);
    
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke,  this,&scGame2::someoneSpoke);
    ofAddListener(mTimerAfterText.timerEnd,         this,&scGame2::timerAfterTextEnd);
    ofAddListener(myInputManager.readyForNewText,   this,&scGame2::readyForNewText);
    
//    // Erase all words of every one
//    bigPlayerManager().freshRestart();
    
    myInputManager.resetInputs();
    
    // On ne refait pas ca si on vient de l'indice
    if(fromScreen->getSceneID() != HINT){
        
        // Reset winner
        bigPlayerManager().setWinnerUserId(0);

        // Load the next enigma
        bigEnigmaManager().pickNewEnigma(IMAGE_GRID);
        
        //cubes
        myCubeManager.setup(ofPoint(0.2*ofGetWidth(), 0.5*ofGetHeight() - 10, -300), 7, 130);
        //inputs
        myInputManager.setup(ofPoint(0.67 * ofGetWidth(), 0.5 * ofGetHeight()), 0.4 * ofGetWidth(), 75);
        
        myInputManager.resetDuplicates();
        myInputManager.setReadyForNewText();
        myInputManager.setMysteryString(myCubeManager.getContent());
        myInputManager.revealTirrets(&myCubeManager);
        
    }

};

//scene notifications
void scGame2::sceneWillDisappear( ofxScene * toScreen ){
    scGame::sceneWillDisappear(toScreen);
    // Disable timer events
    ofRemoveListener(mTimerSignWin.timerEnd,     this,&scGame2::timerSignWinEnd);
    
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
    
    if(bigPlayerManager().getWinnerUserId() > 0){
        myCubeManager.rotateAllToWhite();
    }
    
}
// VICTORY Event , go to scene you prefer
void scGame2::timerSignWinEnd(){
    scGame::timerSignWinEnd();
    ofxSceneManager::instance()->goToScene(VICTORY, true);
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
