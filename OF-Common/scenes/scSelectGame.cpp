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
    scSelect::sceneWillAppear(fromScreen);
    mPlayerMessage = "";
    
    // Erase all words of every one
    mTimerSignAnimation.startTimer(2);
    mTimerEraseWord.startTimer(2);

    // Player manager events
    ofAddListener(mTimerSignAnimation.timerEnd      ,this,&scSelectGame::timerSignAnimationEnd);
    
};

//scene notifications
void scSelectGame::sceneWillDisappear( ofxScene * toScreen ){
    
    // reset our scene when we appear
    scSelect::sceneWillDisappear(toScreen);

    bigPlayerManager().stopSign(1);
    bigPlayerManager().stopSign(2);
    bigPlayerManager().stopSign(3);
    
    // Player manager events
    ofRemoveListener(mTimerSignAnimation.timerEnd       ,this,&scSelectGame::timerSignAnimationEnd);
    
}

void scSelectGame::timerSignAnimationEnd(){
    
    string signMessage;
    
    mTimerSignAnimation.startTimer(2 + ofRandom(-1, 1));
    bigPlayerManager().stopSign(numPlayer);
    
//    numPlayer++;
//    if(numPlayer>3){
//        numPlayer = 1;
//    }
    
    int newPlayer;
    do{
        newPlayer = (int)ofRandom(1, 4);
    }while(numPlayer == newPlayer);
    
    numPlayer = newPlayer;
    
    int idxMesssage = (int)ofRandom(0, 3);
    // Draw players
    switch (idxMesssage) {
        case 0:
            signMessage = "Mot\nmasqué";
            break;
        case 1:
            signMessage = "Mot\nbrassé";
            break;
        case 2:
            signMessage = "Mes mots\nrient";
            break;
            
        default:
            break;
    }
    
    bigPlayerManager().startSign(numPlayer, signMessage);
    
}

