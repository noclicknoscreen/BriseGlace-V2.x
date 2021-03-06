//
//  scGame1.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame1.h"

//=======================================================================
//
//======= MOT MASQUE ====================================================
//
//=======================================================================


void scGame1::setup(){  //load your scene 1 assets here...
    scGame::setup();
    ofLogNotice() << "Game 1 : Setup !";
    
    group.setName("Game1");
    group.add(lightPosX.set("lightPosX", 1600, -3000, 3000));
    group.add(lightPosY.set("lightPosY", 120, -3000, 3000));
    group.add(lightPosZ.set("lightPosZ", 0, -3000, 3000));
    
    group.add(orientationX.set("orientationX", 0, 0, 360));
    group.add(orientationY.set("orientationY", 0, 0, 360));
    group.add(orientationZ.set("orientationZ", 0, 0, 360));
    
    group.add(cutOff.set("cutOff", 0, 0, 360));
    group.add(concentration.set("concentration", 0, 0, 180));
    group.add(cubesRotationSpeed.set("cubesRotationSpeed", 5, 0.1, 20));
    group.add(alphaDecay.set("alphaDecay", 0.01, 0.01, 0.03));
    
    gui.setup(group);
    gui.loadFromFile(settingsFileNameGame1);
    
    bDrawGui=false;
    
    mGameName = "MOT MASQUÉ";
    mConsigne1 = "ON TE DONNE DES LETTRES SI TU NOUS PARLES À L'OREILLE !";
    mConsigne2 = "";
    
};

void scGame1::update(float dt){ //update scene 1 here

    scGame::update(dt);
    
    myCubeManager.update(ofPoint(lightPosX, lightPosY, lightPosZ), ofPoint(orientationX, orientationY, orientationZ), cutOff, concentration, cubesRotationSpeed);
    
    int id = myInputManager.update(&myCubeManager, alphaDecay);
    if(id != 0)
    {
//        drawWinnerSign = true;
        bigPlayerManager().setWinnerUserId(id);
        bigPlayerManager().startSign(id, "C'est gagné !", 0.4f);
        restartTimerSignWin();
        stopHint();
        ofRemoveListener(bigPlayerManager().someoneSpoke,this,&scGame1::someoneSpoke);
    }

    // Update timers
    mTimerSignWin.update(dt);
    
    if(myInputManager.isReadyForNewText() && bigPlayerManager().getWinnerUserId() == 0){
        mTimerBeforeHint.resume();
    }else{
        mTimerBeforeHint.pause();
        // Stop display Hint
        stopHint();
//        bigPlayerManager().stopSign(hintUserId);
    }
    
};

void scGame1::draw(){ //draw scene 1 here
    
    //GUI
    if(bDrawGui){
        ofDisableLighting();
        gui.draw();
    }
    
    // Draw mother of draw
    scGame::draw();
    
    // Draw cubes
    myCubeManager.draw();
    // Draw floating words
    myInputManager.draw();
    
    // Draw players
    bigPlayerManager().draw();
    
};

//--------------------------------------------------------------
void scGame1::keyPressed(int key){
    
    if(key=='l')
        myCubeManager.rotateToLetter(0);
    if(key=='w')
        myCubeManager.rotateToWood(0);
    if(key=='W')
        myCubeManager.rotateToWhite(0);
    if(key == 's') {
        gui.saveToFile(settingsFileNameGame1);
    }
    if(key == 'l') {
        gui.loadFromFile(settingsFileNameGame1);
    }
    
    if(key==' ' )
        bDrawGui = !bDrawGui;
    
}

//scene notifications
void scGame1::sceneWillAppear( ofxScene * fromScreen ){
    
    // reset our scene when we appear
    scGame::sceneWillAppear(fromScreen);
    // Player manager events
    ofAddListener(mTimerSignWin.timerEnd,    this,&scGame1::timerSignWinEnd);
    
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke,this,&scGame1::someoneSpoke);
    
    // Erase previous inputs
    myInputManager.resetInputs();
    
//    // Erase all words of every one
//    bigPlayerManager().freshRestart();
//
    // On ne refiat pas ca si on vient de l'indice
    if(fromScreen->getSceneID() != HINT){
        
        // Load the next enigma
        bigEnigmaManager().pickNewEnigma(MOTUS);
        
        // Reset winner
        bigPlayerManager().setWinnerUserId(0);

        //cubes
        myCubeManager.setup(ofPoint(0.5*ofGetWidth(), 0.4*ofGetHeight(), -300), cEspacementCube, 150);
        
        //inputs
        myInputManager.setup(ofPoint(0.5*ofGetWidth(), 0.6*ofGetHeight()), 0.8 * ofGetWidth(), 75);
        
        //
        string solution = bigEnigmaManager().getCurrentEnigma()->getSolution();
        myCubeManager.getWord(utils::toWString(solution));
        myInputManager.resetDuplicates();
        myInputManager.setReadyForNewText();
        myInputManager.setWordToFind(utils::toUpperCase(solution));
        myInputManager.revealTirrets(&myCubeManager);
        
    }

    
};

//scene notifications
void scGame1::sceneWillDisappear( ofxScene * toScreen ){
    scGame::sceneWillDisappear(toScreen);
    
    // Disable timer events
    ofRemoveListener(mTimerSignWin.timerEnd,     this,&scGame1::timerSignWinEnd);
    
    // Player manager events
    ofRemoveListener(bigPlayerManager().someoneSpoke,   this,&scGame1::someoneSpoke);

}

// Events callback -----------------------------------
// Speaking event
void scGame1::someoneSpoke(player & _player){
    scGame::someoneSpoke(_player);
    
    if(myInputManager.isReadyForNewText()){
        myInputManager.getNewText(_player);
    }
    
    if(bigPlayerManager().getWinnerUserId() > 0){
        myCubeManager.colorizeAllCubes(_player.getColor());
        myCubeManager.rotateAllToLetter();
    }
    
}

// VICTORY Event , go to scene you prefer
void scGame1::timerSignWinEnd(){
    scGame::timerSignWinEnd();
    ofxSceneManager::instance()->goToScene(VICTORY, true);
}

