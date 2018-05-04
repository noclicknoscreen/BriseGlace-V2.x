//
//  scInitialize.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scInitialize.h"

void scInitialize::setup(){  //load your scene 1 assets here...
    ofLogNotice() << "Initialisation : Setup !";
    myFont.load("Folktale.ttf", 28, true, true);
    
};


void scInitialize::update(){ //update scene 1 here
};

void scInitialize::draw(){ //draw scene 1 here
    
    string message = "Initialisation...";
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::black);
    ofPushMatrix();
    
    ofRectangle bounds = myFont.getStringBoundingBox(message, 0, 0);
    ofTranslate(0.5 * (ofGetWidth() - bounds.width), 0.5 * (ofGetHeight() - bounds.height));
    myFont.drawString(message, 0, 0);
    
    ofPopMatrix();
    ofPopStyle();
    
};

//scene notifications
void scInitialize::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
};

//scene notifications
void scInitialize::sceneWillDisappear( ofxScene * toScreen ){
}
