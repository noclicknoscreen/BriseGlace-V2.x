//
//  scGame2.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame2.h"

void scGame2::setup(){  //load your scene 1 assets here...
    ofLogNotice() << "Game 2 : Setup !";
    myFont.load("Folktale.ttf", 28, true, true);
    
};


void scGame2::update(){ //update scene 1 here
};

void scGame2::draw(){ //draw scene 1 here
    
    string message = "Game 2 : Grille / Labyrinthe";
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::green);
    ofPushMatrix();
    
    ofRectangle bounds = myFont.getStringBoundingBox(message, 0, 0);
    ofTranslate(0.5 * (ofGetWidth() - bounds.width), 0.5 * (ofGetHeight() - bounds.height));
    myFont.drawString(message, 0, 0);
    
    ofPopMatrix();
    ofPopStyle();
    
};

//scene notifications
void scGame2::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
};

//scene notifications
void scGame2::sceneWillDisappear( ofxScene * toScreen ){
}
