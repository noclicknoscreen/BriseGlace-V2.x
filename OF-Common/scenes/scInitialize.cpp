//
//  scInitialize.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scInitialize.h"

void scInitialize::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Initialisation : Setup !";
};


void scInitialize::update(float dt){ //update scene 1 here
    
    // update the timer this frame
    dt = ofGetElapsedTimeMillis() - startTime;
    timerValue = 10000 - dt;
    
    if(timerValue <= 0 && !bTimerReached) {
        bTimerReached = true;
        ofNotifyEvent(endSceneEvent, this);
        ofLogNotice() << "End of Timer !!!";
    }

};

void scInitialize::draw(){ //draw scene 1 here
    
    string message = "Initialisation...";
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::black);
    ofPushMatrix();
    
    ofRectangle bounds = myFont24.getStringBoundingBox(message, 0, 0);
    ofTranslate(0.5 * (ofGetWidth() - bounds.width), 0.5 * (ofGetHeight() - bounds.height));
    myFont24.drawString(message, 0, 0);
    myFont24.drawString(ofToString(timerValue), 0, 50);
    
    ofPopMatrix();
    ofPopStyle();
    
};

//scene notifications
void scInitialize::sceneWillAppear( ofxScene * fromScreen ){
    // reset timer
    startTime = ofGetElapsedTimeMillis();  // get the start time
    bTimerReached = false;
};

//scene notifications
void scInitialize::sceneWillDisappear( ofxScene * toScreen ){
}
