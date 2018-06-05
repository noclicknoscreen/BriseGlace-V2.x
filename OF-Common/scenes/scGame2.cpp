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
    
    if(bigPlayerManager().getWinnerUserId() == 0){
        // Input word (who wins)
        myInputManager.update(&myCubeManager);
    }
    
    // Update timers
    mTimer.update(dt);
    timerSignHint.update(dt);
    
//    // We update if the input manager is ok with it, even if we win before the end of animations
//    if(myInputManager.isReadyForNewText()){
        timerSignWin.update(dt);
//    }
    
    // update a timer for post animation
    mTimerAfterText.update(dt);
    
    mTimer.update(dt);
    
};

void scGame2::draw(){ //draw scene 1 here

    //GUI
    if(bDrawGui){
        gui.draw();
    }
    
    // Draw Title
    scScene::drawTitle("Mes mots rient");
    scScene::drawSubTitle("Prochainement dans votre gare...");

    // Draw cubes
    myCubeManager.draw();
    // Draw floating words
    myInputManager.draw();

    // Draw players
    bigPlayerManager().draw();
    
    if(drawWinnerSign)
        bigPlayerManager().draw(bigPlayerManager().getWinnerUserId(), "c'est gagné");
    else if(drawHintSign)
        bigPlayerManager().draw(hintUserId, "veux-tu un indice ?");
    else
        bigPlayerManager().draw();    // Draw players
    
};

//scene notifications
void scGame2::sceneWillAppear( ofxScene * fromScreen ){
    
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke,  this,&scGame2::someoneSpoke);
    ofAddListener(mTimer.timerEnd,                  this,&scGame2::timerEnd);
    ofAddListener(timerSignWin.timerEnd,            this,&scGame2::timerSignWinEnd);
    ofAddListener(timerSignHint.timerEnd,           this,&scGame2::timerSignHintEnd);
    ofAddListener(mTimerAfterText.timerEnd,         this,&scGame2::timerAfterTextEnd);
    ofAddListener(myInputManager.readyForNewText,   this,&scGame2::readyForNewText);
    
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
        myInputManager.setMysteryString(myCubeManager.getContent());
        myInputManager.revealTirrets(&myCubeManager);
        
    }

    // -- -- -- -- --
    mTimer.startTimer(5);
    // Player manager events
    ofAddListener(mTimer.timerEnd, this, &scGame2::timerEnd);
    
};

//scene notifications
void scGame2::sceneWillDisappear( ofxScene * toScreen ){
    // Player manager events
    ofRemoveListener(bigPlayerManager().someoneSpoke,   this,&scGame2::someoneSpoke);
    ofRemoveListener(mTimer.timerEnd,                   this,&scGame2::timerEnd);
    ofRemoveListener(timerSignWin.timerEnd,             this,&scGame2::timerSignWinEnd);
    ofRemoveListener(timerSignHint.timerEnd,            this,&scGame2::timerSignHintEnd);
    ofRemoveListener(mTimerAfterText.timerEnd,          this,&scGame2::timerAfterTextEnd);
    ofRemoveListener(myInputManager.readyForNewText,    this,&scGame2::readyForNewText);
}

// Events callback -----------------------------------
// Speaking event
void scGame2::someoneSpoke(player & _player){
    scScene::someoneSpoke(_player);
    
    if(myInputManager.isReadyForNewText()){
        myInputManager.getNewText(_player);
    }
    
    mTimer.startTimer(45);
    
    int compare = ofStringTimesInString(utils::toUpperCase(_player.getLastMessage()), utils::toUpperCase(bigEnigmaManager().getCurrentEnigma()->getSolution()));
    if(compare > 0)
    {
        ofLogNotice() << "We have a winner [" << _player.getLastMessage() << "] = [" << bigEnigmaManager().getCurrentEnigma()->getSolution() << "], compare = " << compare;
        bigPlayerManager().setWinnerUserId(_player.getNumber());
        myCubeManager.rotateAllToWhite();
        timerSignWin.startTimer(5);
        drawWinnerSign = true;
    }else{
        ofLogNotice() << "Final comparaison failed [" << _player.getLastMessage() << "] different from [" << bigEnigmaManager().getCurrentEnigma()->getSolution() << "], compare = " << compare;
    }
    
}

void scGame2::timerEnd(){
    // --------------------------------
    drawHintSign = true;
    hintUserId = bigPlayerManager().getRandomPlayer();
    mTimer.startTimer(45);
    timerSignHint.startTimer(5);
}

void scGame2::timerSignWinEnd(){
    
    ofLogNotice() << "fin du timer timerSignWin, go to scene 9 (WIN)";
    // --------------------------------
    timerSignWin.stop();
    ofxSceneManager::instance()->goToScene(VICTORY);
}


void scGame2::timerSignHintEnd(){
    
    ofLogNotice() << "fin du timer timerSignHint, go to scene (HINT)";
    // --------------------------------
    timerSignHint.stop();
    ofxSceneManager::instance()->goToScene(HINT);
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
