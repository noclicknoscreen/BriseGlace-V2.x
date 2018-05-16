//
//  scGame2.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame2.h"

void scGame2::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Game 2 : Setup !";
    myTitle = "Game 2 : Grille / Labyrinthe";
};


void scGame2::update(float dt){ //update scene 1 here
};

void scGame2::draw(){ //draw scene 1 here
    
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::green);
    
    scScene::draw();            // Draw title
    bigPlayerManager().draw();
    
    ofPopStyle();
    
};

//scene notifications
void scGame2::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
};

//scene notifications
void scGame2::sceneWillDisappear( ofxScene * toScreen ){
}
