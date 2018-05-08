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
    
};


void scSelectGame::update(float dt){ //update scene 1 here
};

void scSelectGame::draw(){ //draw scene 1 here
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::black);
    
    scScene::draw();            // Draw title
    myPlayerManager->draw();    // Draw players
    drawCenterText(myPlayerManager->getLastMessage(), 0, 50); // Draw last message
    
    ofPopStyle();
    
};

//scene notifications
void scSelectGame::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
};

//scene notifications
void scSelectGame::sceneWillDisappear( ofxScene * toScreen ){
}
