//
//  scHint.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scHint.h"

void scHint::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Indice : Setup !";
    myTitle = "Ecran d'indices";
};


void scHint::update(float dt){ //update scene 1 here
};

void scHint::draw(){ //draw scene 1 here
    
    
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::black);
    scScene::draw();
    ofPopStyle();
    
};

//scene notifications
void scHint::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
};

//scene notifications
void scHint::sceneWillDisappear( ofxScene * toScreen ){
}
