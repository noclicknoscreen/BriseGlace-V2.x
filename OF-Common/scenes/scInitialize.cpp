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
    myTitle = "Initialisation...";
};


void scInitialize::update(float dt){ //update scene 1 here
    
    // update the timer this frame
    dt = ofGetElapsedTimeMillis() - startTime;
    timerValue = 10000 - dt;
    
    if(timerValue <= 0 && !bTimerReached) {
        bTimerReached = true;
        ofLogNotice() << "End of Timer !!!";
    }

};

void scInitialize::draw(){ //draw scene 1 here
    
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::black);
    
    scScene::draw();            // Draw title
    myPlayerManager->draw();    // Draw players
    
    myText.setText(ofToString(timerValue));
    myText.drawCenter(0.5 * ofGetWidth(), 0.5 * ofGetHeight() + 50);
    
    ofPopStyle();
    
};

//scene notifications
void scInitialize::sceneWillAppear( ofxScene * fromScreen ){
    scScene::sceneWillAppear(fromScreen);
    // reset timer
    startTime = ofGetElapsedTimeMillis();  // get the start time
    bTimerReached = false;
};

//scene notifications
void scInitialize::sceneWillDisappear( ofxScene * toScreen ){
}
