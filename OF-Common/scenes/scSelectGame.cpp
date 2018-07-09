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
    if(mIndexSequence < 5){
        scScene::drawTitle("Bienvenue sur \"Jeux de mô\"", ofColor::black, ofPoint(0, 50));
    }else{
        scScene::drawTitle("Pour choisir un jeu :", ofColor::black, ofPoint(0, 50));
    }
    if(mIndexSequence == 1 || mIndexSequence == 2){
        scScene::drawSubTitle("Vous êtes joueurs ?", ofColor::black, ofPoint(0, 300));
    }
    if(mIndexSequence == 2){
        scScene::drawTitle("Nous oui !", ofColor::black, ofPoint(0, 350));
    }
    if(mIndexSequence == 3){
        scScene::drawSubTitle(utils::cleanString("Les mô, sont des petits cubes dotés d’une oreille, d’un long cou, de deux yeux et d’une bouche."), ofColor::black, ofPoint(0, 300));
        scScene::drawSubTitle(utils::cleanString("Ils vivent dans les gares et répètent tout ce qu’on leur dit !"), ofColor::black, ofPoint(0, 460));
    }
    if(mIndexSequence == 4){
        scScene::drawSubTitle(utils::cleanString("Comme ils n’ont pas beaucoup de mémoire,"), ofColor::black, ofPoint(0, 300));
        scScene::drawSubTitle(utils::cleanString("Aidez-les à retrouver leurs mots perdus..."), ofColor::black, ofPoint(0, 375));
    }
    if(mIndexSequence >= 5){
        scScene::drawTitle(utils::cleanString("À vos marques,"), ofColor::black, ofPoint(0, 300));
    }
    if(mIndexSequence >= 6){
        scScene::drawTitle(utils::cleanString("Prêts,"), ofColor::black, ofPoint(0, 390));
    }
    if(mIndexSequence >= 7){
        scScene::drawTitle(utils::cleanString("Parlez !"), ofColor::black, ofPoint(0, 480));
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
    nextStepSequence();
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
    
    float _width = 0.6f;
    
    // Draw players
    switch (numPlayer) {
        case 1:
            signMessage = "Mot masqué";
            _width = 0.4f;
            break;
        case 2:
            signMessage = "Mot brassé";
            _width = 0.4f;
            break;
        case 3:
            signMessage = "Mes mots rient";
            break;
            
        default:
            break;
    }
    
    bigPlayerManager().startSign(numPlayer, signMessage, _width);
    
}

void scSelectGame::timerEraseWordEnd(){
    mPlayerMessage = "";
    mTimerEraseWord.startTimer(2);
}

void scSelectGame::timerTextSequenceEnd(){
    
    ofLogNotice() << "timerTextSequenceEnd, remaining time : " << ofToString(mTimerTextSequence.getValuef());
    nextStepSequence();
    
}

void scSelectGame::nextStepSequence(){
    if(mIndexSequence == 0){
        mTimerTextSequence.startTimer(cTimerTextSequence1);
        mIndexSequence++;
        
    }else if(mIndexSequence == 1){
        mTimerTextSequence.startTimer(cTimerTextSequence1);
        mIndexSequence++;
        
    }else if(mIndexSequence == 2){
        mTimerTextSequence.startTimer(cTimerTextSequence2);
        mIndexSequence++;
        
    }else if(mIndexSequence == 3){
        mTimerTextSequence.startTimer(cTimerTextSequence2);
        mIndexSequence++;
        
    }else if(mIndexSequence == 4){
        mTimerTextSequence.startTimer(cTimerTextSequence3);
        mIndexSequence++;
        
    }else if(mIndexSequence == 5){
        mTimerTextSequence.startTimer(cTimerTextSequence3);
        mIndexSequence++;
        
    }else if(mIndexSequence == 6){
        mTimerTextSequence.startTimer(cTimerTextSequence3);
        mIndexSequence++;
        
    }else if(mIndexSequence == 7){
        mTimerTextSequence.startTimer(cTimerTextSequence3);
        mIndexSequence++;
        
    }else if(mIndexSequence == 8){
        mTimerTextSequence.startTimer(cTimerTextSequence3);
        mIndexSequence++;
        
    }else{
        mTimerTextSequence.stop();
    }
    
}
