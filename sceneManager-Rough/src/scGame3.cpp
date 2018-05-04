//
//  scGame3.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame3.h"

void scGame3::setup(){  //load your scene 1 assets here...
    ofLogNotice() << "Game 3 : Setup !";
    myFont.load("Folktale.ttf", 28, true, true);
    
};


void scGame3::update(){ //update scene 1 here
};

void scGame3::draw(){ //draw scene 1 here
    
    string message = "Game 3 : Boggle";
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::blue);
    ofPushMatrix();
    
    ofRectangle bounds = myFont.getStringBoundingBox(message, 0, 0);
    ofTranslate(0.5 * (ofGetWidth() - bounds.width), 0.5 * (ofGetHeight() - bounds.height));
    myFont.drawString(message, 0, 0);
    
    ofPopMatrix();
    ofPopStyle();
    
};

//scene notifications
void scGame3::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
};

//scene notifications
void scGame3::sceneWillDisappear( ofxScene * toScreen ){
}
