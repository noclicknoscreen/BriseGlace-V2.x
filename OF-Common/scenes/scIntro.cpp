//
//  scIntro.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scIntro.h"



void scIntro::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Introduction : Setup !";
    
    myTitle = "Vous êtes joueur ? moi oui !";
};


void scIntro::update(float dt){ //update scene 1 here
};

void scIntro::draw(){ //draw scene 1 here

    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::black);
    scScene::draw();
    ofPopStyle();
    
};

//scene notifications
void scIntro::sceneWillAppear( ofxScene * fromScreen ){
    scScene::sceneWillAppear(fromScreen);
};

//scene notifications
void scIntro::sceneWillDisappear( ofxScene * toScreen ){
}
