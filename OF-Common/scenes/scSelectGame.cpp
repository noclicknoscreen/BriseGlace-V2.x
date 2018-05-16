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
    
    myTitle = "Choix du jeu";
    mText = "";
    
};


void scSelectGame::update(float dt){ //update scene 1 here
};

void scSelectGame::draw(){ //draw scene 1 here
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::black);
    
    scScene::draw();            // Draw title
    bigPlayerManager().draw();    // Draw players
    
    // Draw some
    myText.setText(ofToString(mText));
    myText.drawCenter(0.5 * ofGetWidth(), 0.5 * ofGetHeight() + 50);
    
    ofPopStyle();
    
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
    mText = _player.getLastMessage();
}
