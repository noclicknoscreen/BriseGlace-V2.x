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
    
    // ---------------------------------------------------------------------------
    mCartoucheText.init(globalFontName, globalFontSizeMedium);
    mTitle.load(globalFontName, globalFontSizeMedium);
    mSubLine1.load(globalFontName, globalFontSizeBig);
    mSubLine2.load(globalFontName, globalFontSizeMedium);
    
}

void scGame::update(float dt){
    timerBeforeHint.update(dt);
    timerSignHint.update(dt);
    timerSignWin.update(dt);
    timerForceWin.update(dt);
    
    // We re-map the volume between the end and the start of a sequence
    loadNewSequenceImage((int)ofMap(timerForceWin.getValuef(), 0, 1, mSequenceLen - 1, 0, true));

    // -----------------------------------------------------------------
    // Draw title and consignes
    mCartoucheText.setColor(0, 0, 0, 255);
    // -----------------------------------------------------------------
    
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
    
    // Dessin du compteur ----------------------------------------------
    if(mSequenceImg.isAllocated()){
        ofSetColor(255,255,255,255);
        
        ofDisableNormalizedTexCoords();
//        mSequenceImg.draw(ofGetWidth() - 200, ofGetHeight() - 200, 100, 100);
        mSubLine2.drawString(timerForceWin.toString(), ofGetWidth() - 200, ofGetHeight() - 200);
        ofEnableNormalizedTexCoords();
    }
    
    // -----------------------------------------------------------------
    // Draw title and consignes
    ofPushStyle();
    
    
    mCartoucheText.setColor(0, 0, 0, 0);
    ofDisableLighting();
    ofDisableDepthTest();
    ofEnableAlphaBlending();
    ofNoFill();
    ofSetColor(ofColor::black, 0);

    
    ofPoint posTextCartouche(300, 100);
    float   width = 400;
    float   lineH = 65;
    mCartoucheText.setText("BIENVENUS");
    mCartoucheText.wrapTextX(width);
    mCartoucheText.drawCenter(posTextCartouche.x, posTextCartouche.y);
    mCartoucheText.setText("SUR");
    mCartoucheText.wrapTextX(width);
    mCartoucheText.drawCenter(posTextCartouche.x, posTextCartouche.y + lineH);
    mCartoucheText.setText(mGameName);
    mCartoucheText.wrapTextX(width);
    mCartoucheText.drawCenter(posTextCartouche.x, posTextCartouche.y + 2*lineH);
    
    ofSetColor(ofColor::black);
    ofPoint posText(600, 175);
    mTitle.drawString("ICI ON CHERCHE :", posText.x, posText.y);
    mSubLine1.drawString(utils::toUpperCase(bigEnigmaManager().getCurrentEnigma()->getTheme()), posText.x, posText.y + 75);
    mSubLine2.drawString(mConsigne, posText.x, posText.y + 150);
    
    ofPopStyle();
    // -----------------------------------------------------------------
    
}

void scGame::someoneSpoke(player & _player){
    
    scScene::someoneSpoke(_player);
    
    int compare = ofStringTimesInString(utils::toUpperCase(_player.getLastMessage()), utils::toUpperCase(bigEnigmaManager().getCurrentEnigma()->getSolution()));
    if(compare > 0)
    {
        ofLogNotice() << "We have a winner [" << _player.getLastMessage() << "] = [" << bigEnigmaManager().getCurrentEnigma()->getSolution() << "], compare = " << compare;
        bigPlayerManager().setWinnerUserId(_player.getNumber());
        bigPlayerManager().startSign(_player.getNumber(), "C'est gagné !");
        restartTimerSignWin();
        stopHint();
        
    }else{
        ofLogNotice() << "Final comparaison failed [" << _player.getLastMessage() << "] different from [" << bigEnigmaManager().getCurrentEnigma()->getSolution() << "], compare = " << compare;
    }
    
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
    timerForceWin.startTimer(90);
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
    // --------------------------------
    //    drawHintSign = true;
    hintUserId = bigPlayerManager().getRandomPlayer();
    timerSignHint.stop();
    bigPlayerManager().startSign(hintUserId, "C'est perdu !");
    
    restartTimerSignWin();
    
//    ofxSceneManager::instance()->goToScene(VICTORY);
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
    bigPlayerManager().stopSign(4);
    
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
    bigPlayerManager().stopSign(4);
    
    // Disable timer events
    ofRemoveListener(timerBeforeHint.timerEnd,  this,&scGame::timerBeforeHintEnd);
    ofRemoveListener(timerSignHint.timerEnd,    this,&scGame::timerSignHintEnd);
    ofRemoveListener(timerForceWin.timerEnd,    this,&scGame::timerForceWinEnd);

}
