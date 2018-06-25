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
};


void scSelectGame::update(float dt){
    mTimerSignAnimation.update(dt);
    mTimerEraseWord.update(dt);
};

void scSelectGame::draw(){ //draw scene 1 here
    // Draw title
    scScene::drawTitle("Bienvenus sur \"Jeux de mô\"", ofColor::black, ofPoint(0, 50));
    
    scScene::drawSubTitle("Vous êtes joueurs ?", ofColor::black, ofPoint(0, 300));
    scScene::drawTitle("Nous oui !", ofColor::black, ofPoint(0, 350));
    
    scScene::drawSubTitle("Pour commencer,", ofColor::black, ofPoint(0, 500));
    scScene::drawTitle("Dites le nom de votre jeu préféré...", ofColor::black, ofPoint(0, 550));
    
    scScene::drawSpokenWord(mPlayerMessage, mPlayerColor);
    
    bigPlayerManager().draw();
    
};

//scene notifications
void scSelectGame::sceneWillAppear( ofxScene * fromScreen ){
    
    // reset our scene when we appear
    scSelect::sceneWillAppear(fromScreen);
    mPlayerMessage = "";
    
    // Erase all words of every one
//    mTimerSignAnimation.startTimer(2);
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
    
    int idxMesssage;
    do{
        idxMesssage = (int)ofRandom(0, 3);
    }while(numMessage == idxMesssage);
    numMessage = idxMesssage;
    
    // Draw players
    switch (idxMesssage) {
        case 0:
            signMessage = "Mot masqué";
            break;
        case 1:
            signMessage = "Mot brassé";
            break;
        case 2:
            signMessage = "Mes mots rient";
            break;
            
        default:
            break;
    }
    
    bigPlayerManager().startSign(numPlayer, signMessage);
    
}

