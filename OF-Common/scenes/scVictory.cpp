//
//  scVictory.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scVictory.h"

void scVictory::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Victory : Setup !";
    myTitle = "Gagné !";
};


void scVictory::update(float dt){ //update scene 1 here
};

void scVictory::draw(){ //draw scene 1 here
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::black);
    scScene::draw();
    ofPopStyle();
};

//scene notifications
void scVictory::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
};

//scene notifications
void scVictory::sceneWillDisappear( ofxScene * toScreen ){
}
