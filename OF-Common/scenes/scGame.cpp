//
//  scGame.cpp
//  theBigGame
//
//  Created by Sébastien Albert on 06/06/2018.
//
//

#include "scGame.h"

void scGame::setup(){
    
    scScene::setup();
    
    // Check the path of the sequence and do some coffee
    ofDirectory seq("Compteur");
    if(!seq.exists()){
        ofLogError() << "Sequence Compteur does not exist.";
    }else if(!seq.isDirectory()){
        ofLogError() << "Sequence Compteur is not directory.";
    }else{
        seq.allowExt("png");
        mSequenceLen = seq.listDir();
        mSequencePath = "Compteur";
        
        ofLogNotice() << "Sequence Path [" << mSequencePath << "] seems good :) and is [" << mSequenceLen<< "] images long";
        
        // This -1 value force the first load
        mSequenceIdx = -1;
        loadNewSequenceImage(0);
        
    }
    
}

void scGame::update(float dt){
    timerBeforeHint.update(dt);
    timerSignHint.update(dt);
    timerSignWin.update(dt);
    timerForceWin.update(dt);
    
    // We re-map the volume between the end and the start of a sequence
    loadNewSequenceImage((int)ofMap(timerForceWin.getValuef(), 0, 1, mSequenceLen - 1, 0, true));

}


void scGame::loadNewSequenceImage(int _newSequenceIdx){
    
    if(_newSequenceIdx>=0 && _newSequenceIdx<=(mSequenceLen - 1) && _newSequenceIdx != mSequenceIdx){
        
        mSequenceIdx = _newSequenceIdx;
        string imgPath = mSequencePath+"/"+mSequencePath+"_"+ ofToString(mSequenceIdx,4,'0') +".png";
        //        ofLogNotice() << "Image path = " << imgPath;
        if(ofFile(imgPath).exists()){
            mSequenceImg.load(imgPath);
        }else{
            ofLogError() << "Image path [" + imgPath + "] not exists.";
            mSequenceImg.load("void.jpg");
        }
        
    }else{
        //        ofLogNotice() << "Something happened with the sequence index : " << _newSequenceIdx;
    }
    
}

void scGame::draw(){
    if(mSequenceImg.isAllocated()){
        ofSetColor(255,255,255,255);
        
        ofDisableNormalizedTexCoords();
        mSequenceImg.draw(ofGetWidth() - 200, ofGetHeight() - 200, 100, 100);
        ofEnableNormalizedTexCoords();
    }
}

void scGame::someoneSpoke(player & _player){
    
    scScene::someoneSpoke(_player);
    
    // Restart waiting timer
    restartTimerBeforeHint();
    // Stop eventually sign timer
    timerSignHint.stop();
}

void scGame::restartTimerSignHint(){
    ofLogNotice() << "Start timerSignHint, waiting..... ";
    timerSignHint.startTimer(5);
}
void scGame::restartTimerBeforeHint(){
    ofLogNotice() << "Start timerBeforeHint, waiting..... ";
//    drawHintSign = false;
    
    timerBeforeHint.startTimer(30);
}
void scGame::restartTimerSignWin(){
    ofLogNotice() << "Start timerSignWin, waiting..... ";
    timerSignWin.startTimer(5);
}
void scGame::restartTimerForceWin(){
    ofLogNotice() << "Start Timer force win, waiting..... ";
    timerForceWin.startTimer(30);
}

void scGame::stopHint(){
    // Stop display Hint
    bigPlayerManager().stopSign(hintUserId);
    timerSignHint.stop();
}

void scGame::timerBeforeHintEnd(){
    
    ofLogNotice() << "fin du timer beforeHint, 5 seconds and go to hint";
    
    // --------------------------------
//    drawHintSign = true;
    hintUserId = bigPlayerManager().getRandomPlayer();
    bigPlayerManager().startSign(hintUserId, "Veux-tu un indice ?");
//
    timerBeforeHint.stop();
    timerSignHint.startTimer(5);
}

void scGame::timerSignWinEnd(){
    ofLogNotice() << "fin du timer timerSignWin, go to scene 9 (WIN) ";
    // --------------------------------
    // Stop counting
    timerSignWin.stop();
    // Then go to child behaviour
}


void scGame::timerSignHintEnd(){
    ofLogNotice() << "fin du timer timerSignHint, go to scene (HINT) ";
    // --------------------------------
    bigPlayerManager().stopSign(hintUserId);
    timerSignHint.stop();
    ofxSceneManager::instance()->goToScene(HINT);
}

void scGame::timerForceWinEnd(){
    ofLogNotice() << "fin du timer timerForceWin, go to scene 9 (WIN) ";
    // --------------------------------
    // Stop counting
    timerForceWin.stop();
    
    ofxSceneManager::instance()->goToScene(VICTORY);
}

//scene notifications
void scGame::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    
//    drawWinnerSign = false;
//    drawHintSign = false;
    
    // Restart waiting timer
    restartTimerBeforeHint();
    // Restart a timer that we win anytime
    restartTimerForceWin();
    // Stop eventually sign timer
//    restartTimerSignHint();
    timerSignHint.stop();
    
    // Reset all signs
    bigPlayerManager().stopSign(1);
    bigPlayerManager().stopSign(2);
    bigPlayerManager().stopSign(3);
    
    // Player manager events
    ofAddListener(timerBeforeHint.timerEnd, this,&scGame::timerBeforeHintEnd);
    ofAddListener(timerSignHint.timerEnd,   this,&scGame::timerSignHintEnd);
    ofAddListener(timerForceWin.timerEnd,   this,&scGame::timerForceWinEnd);
    
}

void scGame::sceneWillDisappear( ofxScene * toScreen ){
    // reset our scene when we appear
    scScene::sceneWillDisappear(toScreen);
    
    timerBeforeHint.stop();
    timerForceWin.stop();
    
    // Reset all signs
    bigPlayerManager().stopSign(1);
    bigPlayerManager().stopSign(2);
    bigPlayerManager().stopSign(3);
    
    // Disable timer events
    ofRemoveListener(timerBeforeHint.timerEnd,  this,&scGame::timerBeforeHintEnd);
    ofRemoveListener(timerSignHint.timerEnd,    this,&scGame::timerSignHintEnd);
    ofRemoveListener(timerForceWin.timerEnd,   this,&scGame::timerForceWinEnd);

}
