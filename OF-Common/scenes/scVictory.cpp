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
    
    // Draw author
    mAuthorDraw.load(globalFontName, 8);
    
};


void scVictory::update(float dt){ //update scene 1 here
    scScene::update(dt);
    mTimerReading.update(dt);
    if(mTimerReading.isAnimating() == false){
        mTimerScene.update(dt);
    }
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
//    winnerText.draw(ofGetWidth()/2, 0.28 * ofGetHeight());
    winnerText.draw(ofGetWidth()/2, 0.5 * (ofGetHeight() - winnerText.getHeight()));
    
    // ///////////////////////////////////////////////////////////////
    // Draw author
    ofPushStyle();
    
    ofEnableAlphaBlending();
    ofSetColor(ofColor::black, 200);
    
    ofPushMatrix();
    ofTranslate(0.23 * ofGetWidth(), 0.69 * ofGetHeight());
    //    ofRotateZ(-90);
    
    mAuthorDraw.drawString(bigEnigmaManager().getCurrentEnigma()->getAuteurRecompense(), 0, 0);
    
    ofPopStyle();
    ofPopMatrix();
    // ///////////////////////////////////////////////////////////////
    
};

//scene notifications
void scVictory::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    
    // --
    mTimerScene.stop();
    mTimerReading.startTimer(cTimerReadingTimeout);
    
    bigPlayerManager().resetChromiumPages();
    
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke   ,this   ,&scVictory::someoneSpoke);
    ofAddListener(mTimerScene.timerEnd              ,this   ,&scVictory::timerSceneEnd);
    ofAddListener(mTimerReading.timerEnd            ,this   ,&scVictory::timerReadingEnd);
    
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
    
    ofRemoveListener(bigPlayerManager().someoneSpoke    ,this   ,&scVictory::someoneSpoke);
    ofRemoveListener(mTimerScene.timerEnd               ,this   ,&scVictory::timerSceneEnd);
    ofRemoveListener(mTimerReading.timerEnd             ,this   ,&scVictory::timerReadingEnd);
}


void scVictory::endScene(){
    mNumberGames++;
    if(mNumberGames % 5 == 0){
        ofxSceneManager::instance()->goToScene(PARTNERS);
    }else{
        ofxSceneManager::instance()->goToScene(SELECT_GAME);
    }
}

// EVENTS SECTION /////////////////////////////////////////////////////////////
// Speaking event
void scVictory::someoneSpoke(player & _player){
    scScene::someoneSpoke(_player);
    
    if(mTimerReading.isAnimating() == false){
        endScene();
    }
}

// If the time is ended, we go further ---------------------------------------
void scVictory::timerSceneEnd(){
    ofLogNotice()  << "Fin du timer timerEndScene";
    endScene();
}

void scVictory::timerReadingEnd(){
    ofLogNotice()  << "Fin du timer timerEndReading";
    mTimerReading.stop();
    mTimerScene.startTimer(cTimerSceneTimeout);
}

