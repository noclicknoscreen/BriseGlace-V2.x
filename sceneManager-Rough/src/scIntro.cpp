//
//  scIntro.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scIntro.h"

void scIntro::setup(){  //load your scene 1 assets here...
    ofLogNotice() << "Introduction : Setup !";
    myFont.load("Folktale.ttf", 28, true, true);
    
};


void scIntro::update(){ //update scene 1 here
};

void scIntro::draw(){ //draw scene 1 here
    
    string message = "Introduction : Mot caché";
    
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
void scIntro::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
};

//scene notifications
void scIntro::sceneWillDisappear( ofxScene * toScreen ){
}
