//
//  scVictory.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scVictory.h"

void scVictory::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Victory : Setup !";
    
    
    cubeSize = 300;
    mNumberGames = 0;
    
};


void scVictory::update(float dt){ //update scene 1 here
    scScene::update(dt);
    mTimerEndScene.update(dt);
};

void scVictory::draw(){ //draw scene 1 here
    
    ofPushStyle();
    ofEnableSmoothing();
    
    //CUBE + TEXTURE
    ofSetColor(255);
    
    ofEnableDepthTest();
    ofEnableNormalizedTexCoords();
    
    
    ofPushMatrix();
    
    ofTranslate(ofGetWidth()/4 + 100, ofGetHeight()/3 + cubeSize/2 + 50, -cubeSize/2);
    ofRotate(15.0*sin(float(ofGetFrameNum()/100.0))+10, 0, 1, 0);
    ofRotate(3.0*cos(float(ofGetFrameNum()/100.0)), 1, 0, 0);
    woodTexture.bind();
    ofDrawBox(0, 0, 0, cubeSize, cubeSize, cubeSize);
    woodTexture.unbind();
    
    localRewardImage.bind();
    ofDrawBox(0,0, cubeSize/2, cubeSize, cubeSize, 1);
    localRewardImage.unbind();
    
    ofDisableNormalizedTexCoords();
    ofDisableDepthTest();
    
    ofPopMatrix();
    ofPopStyle();
    
    //TEXT
    //    scScene::drawTitle(bigEnigmaManager().getCurrentEnigma()->getSolution(), ofColor::black, ofPoint(0,50));
    scScene::drawTitle(bigEnigmaManager().getCurrentEnigma()->getTitleRecompense(), ofColor::black, ofPoint(0,50));
    
    winnerText.setColor(0, 0, 0, 255);
    winnerText.wrapTextX(0.4 * ofGetWidth());
    winnerText.draw(ofGetWidth()/2, 0.28 * ofGetHeight());
    
};

//scene notifications
void scVictory::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    
    // --
    mTimerEndScene.startTimer(25);
    // Player manager events
    ofAddListener(mTimerEndScene.timerEnd,this,&scVictory::timerEndScene);
    
    winnerText.init(globalFontName, globalFontSizeSmall);
    winnerText.setText(bigEnigmaManager().getCurrentEnigma()->getLegende());
    ofSetBoxResolution(30);
    
    
    ofLogNotice() << "texte de recompense : " <<  bigEnigmaManager().getCurrentEnigma()->getLegende();
    
    localRewardImage = bigEnigmaManager().getCurrentEnigma()->getImageRecompense();
    woodTexture.load("contreplaque.png");
    
};

//scene notifications
void scVictory::sceneWillDisappear( ofxScene * toScreen ){
    scScene::sceneWillDisappear(toScreen);
    
    ofRemoveListener(mTimerEndScene.timerEnd,this,&scVictory::timerEndScene);
}

// EVENTS SECTION /////////////////////////////////////////////////////////////
// If the time is ended, we go further ---------------------------------------
void scVictory::timerEndScene(){
    mNumberGames++;
    if(mNumberGames % 5 == 0){
        ofxSceneManager::instance()->goToScene(PARTNERS);
    }else{
        ofxSceneManager::instance()->goToScene(INTRO);
    }
}

