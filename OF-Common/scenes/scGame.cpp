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
    mCartoucheImg.load("Pancarte/Pancarte-ss-Ombres.png");
    mCartoucheImg.resize(0.5 * mCartoucheImg.getWidth(), 0.5 * mCartoucheImg.getHeight());
    mCartoucheTextTitle.init(globalFontName, globalFontSizeSmall);
    mCartoucheTextSubTi.init(globalFontName, globalFontSizeMedium);
    mTitle.load(globalFontName, globalFontSizeMedium);
    mSubLine1.load(globalFontName, globalFontSizeBig);
    mSubLine2.load(globalFontName, globalFontSizeMedium - 2);
    
    // ---------------------------------------------------------------------------
    petitTrain.load("Train-A01", 2.0, ofPoint(150, 150));
    
    // ---------------------------------------------------------------------------
    // Format 834 x 753
    ofPoint originalSizeGare(834, 753);
    ofPoint originalSizeDepart(295, 531);
    float factorGare = 0.25f;
    float factorDepart = 0.35f;
    
    gare.load("Gare-A01.png");
    gare.resize(factorGare * originalSizeGare.x, factorGare * originalSizeGare.y);
    
    depart.load("DEPART-A01.png");
    depart.resize(factorDepart * originalSizeDepart.x, factorDepart * originalSizeDepart.y);
    
}

void scGame::update(float dt){
    timerBeforeHint.update(dt);
    timerSignHint.update(dt);
    timerSignWin.update(dt);
    timerForceWin.update(dt);
    
    // We re-map the volume between the end and the start of a sequence
    loadNewSequenceImage((int)ofMap(timerForceWin.getValuef(), 0, 1, mSequenceLen - 1, 0, true));

    // ---------------------------------------------------------------------------
    petitTrain.update(dt);
    
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
    
    // -----------------------------------------------------------------
    ofPushStyle();
    
    ofEnableAlphaBlending();
    ofDisableDepthTest();
    ofDisableNormalizedTexCoords();
    
    ofSetColor(255);
    gare.draw(0.85 * ofGetWidth(), 0.715 * ofGetHeight());
    depart.draw(0.02 * ofGetWidth(), 0.72 * ofGetHeight() -5);
    ofPopStyle();
    
    if(mDrawPetitTrain){
        float x = ofMap(timerForceWin.getValuef(), 0.025f, 0.99f, 0.85 * ofGetWidth() + 0.5 * gare.getWidth(), 0, true);
        petitTrain.draw(ofPoint(x, ofGetHeight() - 175));
    }
    
    ofPopStyle();
    
    // -----------------------------------------------------------------
    // Draw title and consignes
    ofPushStyle();
    
    ofDisableLighting();
    ofDisableDepthTest();
    ofEnableAlphaBlending();
    ofDisableNormalizedTexCoords();
    
    ofNoFill();
    
    ofPoint posCartouche(1600, 135);
    ofPoint posText(175, 90);
    
    float   width = 300;
    float   lineH = 65;
    
    
    ofSetColor(ofColor::white, 255);
    
    ofPushMatrix();
    ofTranslate(posCartouche);
    
    mCartoucheImg.draw(- 0.5 * mCartoucheImg.getWidth(), - 0.5 * mCartoucheImg.getHeight());
    
    ofPushMatrix();
    ofRotateZ(-7);
    ofScale(0.7, 0.7);
    
//    mCartoucheTextTitle.setText("BIENVENUE SUR");mCartoucheTextTitle.setColor(255, 255, 255, 255);
//    mCartoucheTextTitle.wrapTextX(width);
//    mCartoucheTextTitle.drawCenter(posTextCartouche.x, posTextCartouche.y);
//    mCartoucheTextTitle.setText("SUR");mCartoucheTextTitle.setColor(255, 255, 255, 255);
//    mCartoucheTextTitle.wrapTextX(width);
//    mCartoucheTextTitle.drawCenter(posTextCartouche.x, posTextCartouche.y + lineH);
    
    mCartoucheTextSubTi.setText(mGameName);mCartoucheTextSubTi.setColor(0, 0, 0	, 255);
    mCartoucheTextSubTi.wrapTextX(width);
    mCartoucheTextSubTi.drawCenter(0, -100);
    
    ofPopMatrix();
    ofPopMatrix();
    
    
    ofSetColor(ofColor::black);
    mTitle.drawString("ICI ON CHERCHE :", posText.x, posText.y);
    mSubLine1.drawString(utils::toUpperCase(bigEnigmaManager().getCurrentEnigma()->getTheme()), posText.x, posText.y + 80);
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
    
    // We can spoke to the app to show or not the hint
    if(hintUserId != 0){
        int compareOui = ofStringTimesInString(utils::toUpperCase(_player.getLastMessage()), utils::toUpperCase("oui"));
        
        int compareNon = ofStringTimesInString(utils::toUpperCase(_player.getLastMessage()), utils::toUpperCase("non"));
        
        if(compareOui > 0){
            // Oui -> indice
            ofxSceneManager::instance()->goToScene(HINT);
        }else if(compareNon > 0){
            // Non -> on arrête
            stopHint();
        }
    }
}

void scGame::restartTimerSignHint(){
    ofLogNotice() << "Start timerSignHint, waiting..... ";
    timerSignHint.startTimer(cTimerSignHint);
}
void scGame::restartTimerBeforeHint(){
    ofLogNotice() << "Start timerBeforeHint, waiting..... ";
    timerBeforeHint.startTimer(cTimerBeforeHint);
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
    hintUserId = 0;
}

void scGame::timerBeforeHintEnd(){
    
    ofLogNotice() << "fin du timer beforeHint, 5 seconds and go to hint";
    
    // --------------------------------
    if(mNbHints < 3){
        
        mNbHints++;
        
        hintUserId = bigPlayerManager().getRandomPlayer();
        bigPlayerManager().startSign(hintUserId, "Veux-tu un indice ?");
        
        timerBeforeHint.stop();
        restartTimerSignHint();
    }
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
    // Stop Drawing Train
    mDrawPetitTrain = false;
    // --------------------------------
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
    
    // Restart waiting timer
    restartTimerBeforeHint();

    // Stop eventually sign timer
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
    
    // On ne refait pas ca si on vient de l'indice
    if(fromScreen->getSceneID() != HINT){
        // Restart a timer that we win anytime
        restartTimerForceWin();
        mNbHints = 0;
        mDrawPetitTrain = true;
    }else{
        // unPause the timer
        timerForceWin.resume();
    }
    
}

void scGame::sceneWillDisappear( ofxScene * toScreen ){
    // reset our scene when we appear
    scScene::sceneWillDisappear(toScreen);
    
    // On ne refait pas ca si on vient de l'indice
    if(toScreen->getSceneID() != HINT){
        // Restart a timer that we win anytime
        timerForceWin.stop();
    }else{
        // Pause the timer
        timerForceWin.pause();
    }
    timerBeforeHint.stop();
    
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
