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
};


void scHint::update(float dt){ //update scene 1 here
};

void scHint::draw(){ //draw scene 1 here
    
    string message = "Ecran d'indices";
    
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
void scHint::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
};

//scene notifications
void scHint::sceneWillDisappear( ofxScene * toScreen ){
}
