//
//  scGame1.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame1.h"

void scGame1::setup(){  //load your scene 1 assets here...
    ofLogNotice() << "Game 1 : Setup !";
    myFont.load("Folktale.ttf", 28, true, true);
    
};


void scGame1::update(){ //update scene 1 here
};

void scGame1::draw(){ //draw scene 1 here
    
    string message = "Game 1 : Mot caché";
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::red);
    ofPushMatrix();
    
    ofRectangle bounds = myFont.getStringBoundingBox(message, 0, 0);
    ofTranslate(0.5 * (ofGetWidth() - bounds.width), 0.5 * (ofGetHeight() - bounds.height));
    myFont.drawString(message, 0, 0);
    
    ofPopMatrix();
    ofPopStyle();
};

//scene notifications
void scGame1::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
};

//scene notifications
void scGame1::sceneWillDisappear( ofxScene * toScreen ){
}
