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
    
};


void scSelectGame::update(float dt){ //update scene 1 here
};

void scSelectGame::draw(){ //draw scene 1 here
    // Draw title
    scScene::drawTitle("Dites le nom d'un jeu pour commencer");
    scScene::drawSpokenWord(mPlayerMessage, mPlayerColor);
    
    // Draw players
    bigPlayerManager().draw();
    
};

//scene notifications
void scSelectGame::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    
    // Erase all words of every one
    bigPlayerManager().freshRestart();

    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke,this,&scSelectGame::someoneSpoke);
};

//scene notifications
void scSelectGame::sceneWillDisappear( ofxScene * toScreen ){
    // Player manager events
    ofRemoveListener(bigPlayerManager().someoneSpoke,this,&scSelectGame::someoneSpoke);
}

// Speaking event
void scSelectGame::someoneSpoke(player & _player){
    scScene::someoneSpoke(_player);
    
    mPlayerMessage = _player.getLastMessage();
    mPlayerColor = _player.getColor();
    
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
    
    // Choix du jeu 3 : Mot Brassé
    if(ofStringTimesInString(mPlayerMessage, "brassé") > 0){
        ofxSceneManager::instance()->goToScene(GAME3);
    }
    if(ofStringTimesInString(mPlayerMessage, "brasser") > 0){
        ofxSceneManager::instance()->goToScene(GAME3);
    }
    
}
