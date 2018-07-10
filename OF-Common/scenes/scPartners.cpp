//
//  scPartners.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scPartners.h"

#define timerTexteDuration 2

void scPartners::setup(){  //load your scene 1 assets here...
    scScene::setup();
    
    ofLogNotice() << "Partners";
    
    partnerImage.load("Credit-BriseGlace-A04.png");
};

void scPartners::update(float dt){
    // upate timer
    mTimerDisplay.update(dt);
}


void scPartners::draw(){ //draw scene 1 here
    ofPushStyle();
    ofSetColor(ofColor::white, 255);
    ofEnableAlphaBlending();
    ofDisableDepthTest();
    ofDisableNormalizedTexCoords();
    // Draw single image
//    partnerImage.draw(0.5 * ofGetWidth(),0.5 * ofGetHeight(), 100, 100);
    partnerImage.draw(0.5 * (ofGetWidth() - partnerImage.getWidth()), 0.5 * (ofGetHeight() - partnerImage.getHeight()));
    ofPopStyle();
};

//scene notifications
void scPartners::sceneWillAppear( ofxScene * fromScreen ){
    scScene::sceneWillAppear(fromScreen);
    
    // start counting
    mTimerDisplay.startTimer(20);
    
    // Events ///////////////////////////////////////////////////////////////////////////
    ofAddListener(mTimerDisplay.timerEnd    ,this,&scPartners::timerDisplayEnd);
    
};

//scene notifications
void scPartners::sceneWillDisappear( ofxScene * toScreen ){
    scScene::sceneWillDisappear(toScreen);
    
    // Events ///////////////////////////////////////////////////////////////////////////
    ofRemoveListener(mTimerDisplay.timerEnd ,this,&scPartners::timerDisplayEnd);
    
}

// EVENTS ////////////////////////////////////////////////////////////////////////////////////////////
// Speaking event
void scPartners::timerDisplayEnd(){
    ofxSceneManager::instance()->goToScene(SELECT_GAME);
}



