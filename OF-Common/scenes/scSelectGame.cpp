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
    numMessage = 0;
    mIndexSequence = 0;
};


void scSelectGame::update(float dt){
    mTimerSignAnimation.update(dt);
    mTimerTextSequence.update(dt);
    mTimerEraseWord.update(dt);
};

void scSelectGame::draw(){ //draw scene 1 here
    // Draw title
    if(mIndexSequence >= 2){
        scScene::drawTitle("Bienvenue sur \"Jeux de mô\"", ofColor::black, ofPoint(0, 50));
    }
    
    if(mIndexSequence <= 2){
        scScene::drawSubTitle("Vous êtes joueurs ?", ofColor::black, ofPoint(0, 300));
        if(mIndexSequence >= 1){
            scScene::drawTitle("Nous oui !", ofColor::black, ofPoint(0, 350));
        }
    }
    
    if(mIndexSequence >= 3){
        scScene::drawSubTitle("Pour commencer,", ofColor::black, ofPoint(0, 300));
        scScene::drawTitle("Dites le nom de votre jeu préféré...", ofColor::black, ofPoint(0, 350));
    }
    scScene::drawSpokenWord(mPlayerMessage, mPlayerColor);
    
    bigPlayerManager().draw();
    
};

//scene notifications
void scSelectGame::sceneWillAppear( ofxScene * fromScreen ){
    
    // reset our scene when we appear
    scSelect::sceneWillAppear(fromScreen);
    mPlayerMessage = "";
    mIndexSequence = 0;
    
    mTimerTextSequence.startTimer(1);
    // Erase all words of every one
    mTimerEraseWord.startTimer(2);
    
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke   ,this,&scSelectGame::someoneSpoke);
    ofAddListener(mTimerTextSequence.timerEnd      ,this,&::scSelectGame::timerTextSequenceEnd);
    ofAddListener(mTimerEraseWord.timerEnd          ,this,&scSelectGame::timerEraseWordEnd);
    ofAddListener(mTimerSignAnimation.timerEnd      ,this,&scSelectGame::timerSignAnimationEnd);
    
};

//scene notifications
void scSelectGame::sceneWillDisappear( ofxScene * toScreen ){
    
    // reset our scene when we appear
    scSelect::sceneWillDisappear(toScreen);
    
    bigPlayerManager().stopSign(1);
    bigPlayerManager().stopSign(2);
    bigPlayerManager().stopSign(3);
    bigPlayerManager().stopSign(4);
    
    // Player manager events
    ofRemoveListener(bigPlayerManager().someoneSpoke    ,this,&scSelectGame::someoneSpoke);
    ofRemoveListener(mTimerTextSequence.timerEnd      ,this,&scSelectGame::timerTextSequenceEnd);
    ofRemoveListener(mTimerEraseWord.timerEnd          ,this,&scSelectGame::timerEraseWordEnd);
    ofRemoveListener(mTimerSignAnimation.timerEnd       ,this,&scSelectGame::timerSignAnimationEnd);
    
}

// EVENTS ////////////////////////////////////////////////////////////////////////////////////////////
// Speaking event
void scSelectGame::someoneSpoke(player & _player){
    scSelect::someoneSpoke(_player);
}

void scSelectGame::timerSignAnimationEnd(){
    
    string signMessage;
    
    mTimerSignAnimation.startTimer(2 + ofRandom(-1, 1));
    bigPlayerManager().stopSign(numPlayer);
    
    numPlayer++;
    if(numPlayer>3){
        numPlayer = 1;
    }
    
    //    int newPlayer;
    //    do{
    //        newPlayer = (int)ofRandom(1, 4);
    //    }while(numPlayer == newPlayer);
    //    numPlayer = newPlayer;
    
    //    int idxMesssage;
    //    do{
    //        idxMesssage = (int)ofRandom(0, 3);
    //    }while(numMessage == idxMesssage);
    //    numMessage = idxMesssage;
    
    // Draw players
    switch (numPlayer) {
        case 1:
            signMessage = "Mô masqué";
            break;
        case 2:
            signMessage = "Mô brassé";
            break;
        case 3:
            signMessage = "Mes mô rient";
            break;
            
        default:
            break;
    }
    
    bigPlayerManager().startSign(numPlayer, signMessage);
    
}

void scSelectGame::timerEraseWordEnd(){
    mPlayerMessage = "";
    mTimerEraseWord.startTimer(2);
}

void scSelectGame::timerTextSequenceEnd(){
    if(mIndexSequence <= 3){
        mTimerTextSequence.startTimer(1);
        mIndexSequence++;
    }else{
        mTimerTextSequence.stop();
    }
}


