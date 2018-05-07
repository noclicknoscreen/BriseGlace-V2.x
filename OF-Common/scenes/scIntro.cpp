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
};


void scIntro::update(float dt){ //update scene 1 here
};

void scIntro::draw(){ //draw scene 1 here
    
    string message = "Vous êtes joueur ? moi oui !";
    
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
void scIntro::sceneWillAppear( ofxScene * fromScreen ){
};

//scene notifications
void scIntro::sceneWillDisappear( ofxScene * toScreen ){
}
