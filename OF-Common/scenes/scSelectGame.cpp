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
    scScene::drawTitle("Choix du jeu");
    scScene::drawSpokenWord(mPlayerMessage, mPlayerColor);
    
    // Draw players
    bigPlayerManager().draw();
    
};

//scene notifications
void scSelectGame::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
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
    
}
