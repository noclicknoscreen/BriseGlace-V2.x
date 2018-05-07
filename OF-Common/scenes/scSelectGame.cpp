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
};


void scSelectGame::update(float dt){ //update scene 1 here
};

void scSelectGame::draw(){ //draw scene 1 here
    
    string message = "Choix du jeu";
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::black);
    ofPushMatrix();
    
    ofRectangle bounds = myFont24.getStringBoundingBox(message, 0, 0);
    ofTranslate(0.5 * (ofGetWidth() - bounds.width), 0.5 * (ofGetHeight() - bounds.height));
    myFont24.drawString(message, 0, 0);
    
    ofPopMatrix();
    ofPopStyle();
    
};

//scene notifications
void scSelectGame::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
};

//scene notifications
void scSelectGame::sceneWillDisappear( ofxScene * toScreen ){
}
