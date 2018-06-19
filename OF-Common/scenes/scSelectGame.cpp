//
//  scSelectGame.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scSelectGame.h"

void scSelectGame::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Select a game : Setup !";
    
    mPlayerMessage = "";
    numPlayer = 1;
};


void scSelectGame::update(float dt){
    mTimerSignAnimation.update(dt);
    mTimerEraseWord.update(dt);
};

void scSelectGame::draw(){ //draw scene 1 here
    // Draw title
    scScene::drawSubTitle("Dites le nom d'un jeu pour commencer");
    scScene::drawSpokenWord(mPlayerMessage, mPlayerColor);
    
    bigPlayerManager().draw();
    
};

//scene notifications
void scSelectGame::sceneWillAppear( ofxScene * fromScreen ){
    
    
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    mPlayerMessage = "";
    
    // Erase all words of every one
    mTimerSignAnimation.startTimer(2);
    mTimerEraseWord.startTimer(2);

    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke   ,this,&scSelectGame::someoneSpoke);
    ofAddListener(mTimerSignAnimation.timerEnd      ,this,&scSelectGame::timerSignAnimationEnd);
    ofAddListener(mTimerEraseWord.timerEnd      ,this,&scSelectGame::timerEraseWordEnd);
};

//scene notifications
void scSelectGame::sceneWillDisappear( ofxScene * toScreen ){
    // reset our scene when we appear
    scScene::sceneWillDisappear(toScreen);

    bigPlayerManager().stopSign(1);
    bigPlayerManager().stopSign(2);
    bigPlayerManager().stopSign(3);
    
    // Player manager events
    ofRemoveListener(bigPlayerManager().someoneSpoke    ,this,&scSelectGame::someoneSpoke);
    ofRemoveListener(mTimerSignAnimation.timerEnd      ,this,&scSelectGame::timerSignAnimationEnd);
    ofRemoveListener(mTimerEraseWord.timerEnd      ,this,&scSelectGame::timerEraseWordEnd);
}

// Speaking event
void scSelectGame::someoneSpoke(player & _player){
    scScene::someoneSpoke(_player);
    
    mPlayerMessage = _player.getLastMessage();
    mPlayerColor = _player.getColor();
    mTimerEraseWord.startTimer(2);
    
    ofLogNotice() << "Last spoken word is : " << _player.getLastMessage();
    // Choix du jeu 1 : Mot Masqué
    if(ofStringTimesInString(mPlayerMessage, "masqué") > 0){
        ofxSceneManager::instance()->goToScene(GAME1);
    }
    if(ofStringTimesInString(mPlayerMessage, "masquer") > 0){
        ofxSceneManager::instance()->goToScene(GAME1);
    }
    
    // Choix du jeu 2 : Mes mots rient
    if(ofStringTimesInString(mPlayerMessage, "rient") > 0){
        ofxSceneManager::instance()->goToScene(GAME2);
    }
    if(ofStringTimesInString(mPlayerMessage, "riz") > 0){
        ofxSceneManager::instance()->goToScene(GAME2);
    }
    if(ofStringTimesInString(mPlayerMessage, "memory") > 0){
        ofxSceneManager::instance()->goToScene(GAME2);
    }
    if(ofStringTimesInString(mPlayerMessage, "memories") > 0){
        ofxSceneManager::instance()->goToScene(GAME2);
    }
    
    // Choix du jeu 3 : Mot Brassé
    if(ofStringTimesInString(mPlayerMessage, "brassé") > 0){
        ofxSceneManager::instance()->goToScene(GAME3);
    }
    if(ofStringTimesInString(mPlayerMessage, "brasser") > 0){
        ofxSceneManager::instance()->goToScene(GAME3);
    }
    
}

void scSelectGame::timerSignAnimationEnd(){
    
    string signMessage;
    
    mTimerSignAnimation.startTimer(2 + ofRandom(-1, 1));
    bigPlayerManager().stopSign(numPlayer);
    
    numPlayer++;
    if(numPlayer>3){
        numPlayer = 1;
    }
    
//    // Draw players
    switch (numPlayer) {
        case 1:
            signMessage = "Mot masqué";
            break;
        case 2:
            signMessage = "Mot brassé";
            break;
        case 3:
            signMessage = "Mes mots rient";
            break;
            
        default:
            break;
    }
    
    bigPlayerManager().startSign(numPlayer, signMessage);
    
}

void scSelectGame::timerEraseWordEnd(){
    //ofLogNotice() << "Erase word to avoid bullshits";
    mPlayerMessage = "";
    mTimerEraseWord.stop();
}
