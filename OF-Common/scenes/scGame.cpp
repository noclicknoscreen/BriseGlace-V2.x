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
    mSubLine2.load(globalFontName, globalFontSizeMedium - 5);
    mSubLine3.load(globalFontName, globalFontSizeMedium - 5);
    
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
    mTimerBeforeHint.update(dt);
    mTimerSignHint.update(dt);
    mTimerSignWin.update(dt);
    mTimerForceWin.update(dt);
    mTimerTrain.update(dt);
    
    // We re-map the volume between the end and the start of a sequence
    loadNewSequenceImage((int)ofMap(mTimerForceWin.getValuef(), 0, 1, mSequenceLen - 1, 0, true));

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
    
    if(mTimerTrain.isAnimating()){
        // This a map with the value in seconds
        // 0            => start position (Left)
        // end timer    => le train arrive en gare
        float x = ofMap(mTimerTrain.getValuef(), 1, 0, 0.02 * ofGetWidth(), 0.85 * ofGetWidth() + 0.5 * gare.getWidth(), true);
        petitTrain.draw(ofPoint(x, ofGetHeight() - 180));
    }
    
//    ofPopStyle();
    
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
    mSubLine2.drawString(mConsigne1, posText.x, posText.y + 150);
    mSubLine3.drawString(mConsigne2, posText.x, posText.y + 200);
    
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
        bigPlayerManager().startSign(_player.getNumber(), "C'est gagné !", 0.4f);
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
    
    int compareIndice = ofStringTimesInString(utils::toUpperCase(_player.getLastMessage()), utils::toUpperCase("indice"));
    if(compareIndice > 0)
    {
        // Oui -> indice
        ofxSceneManager::instance()->goToScene(HINT);
    }
    

    
}

void scGame::restartTimerSignHint(){
    ofLogNotice() << "Start timerSignHint, waiting..... ";
    mTimerSignHint.startTimer(cTimerSignHint);
}
void scGame::restartTimerBeforeHint(){
    ofLogNotice() << "Start timerBeforeHint, waiting..... ";
    mTimerBeforeHint.startTimer(cTimerBeforeHint);
}
void scGame::restartTimerSignWin(){
    ofLogNotice() << "Start timerSignWin, waiting..... ";
    mTimerSignWin.startTimer(cTimerSignWin);
}
void scGame::restartTimerForceWin(){
    ofLogNotice() << "Start Timer force win, waiting..... ";
    mTimerForceWin.startTimer(cTimerForceWin);
    mTimerTrain.startTimer(cTimerTrain);
}

void scGame::stopHint(){
    // Stop display Hint
    bigPlayerManager().stopSign(hintUserId);
//    mTimerSignHint.stop();
    mTimerSignHint.pause();
    hintUserId = 0;
}

void scGame::timerBeforeHintEnd(){
    
    ofLogNotice() << "fin du timer beforeHint, 5 seconds and go to hint";
    
    // --------------------------------
    if(mNbHints < 3){
        
        mNbHints++;
        
        hintUserId = bigPlayerManager().getRandomPlayer();
        bigPlayerManager().startSign(hintUserId, "Veux-tu un indice ?");
        
        mTimerBeforeHint.stop();
        restartTimerSignHint();
    }
}

void scGame::timerSignWinEnd(){
    ofLogNotice() << "fin du timer timerSignWin, go to scene 9 (WIN) ";
    // --------------------------------
    // Stop counting
    mTimerSignWin.stop();
    // Then go to child behaviour
}


void scGame::timerSignHintEnd(){
    ofLogNotice() << "fin du timer timerSignHint, go to scene (HINT) ";
    // --------------------------------
    bigPlayerManager().stopSign(hintUserId);
    mTimerSignHint.stop();
    ofxSceneManager::instance()->goToScene(HINT);
}

void scGame::timerForceWinEnd(){
    ofLogNotice() << "fin du timer timerForceWin, launch sign timer ";
    // --------------------------------
    // Stop counting
    mTimerForceWin.stop();
    // --------------------------------
    hintUserId = bigPlayerManager().getRandomPlayer();
    mTimerSignHint.stop();
    bigPlayerManager().startSign(hintUserId, "Dommage ! La réponse était...", 0.85f);
    
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
    mTimerSignHint.stop();
    mTimerSignWin.stop();
    
    // Reset all signs
    bigPlayerManager().stopSign(1);
    bigPlayerManager().stopSign(2);
    bigPlayerManager().stopSign(3);
    bigPlayerManager().stopSign(4);
    
    // Player manager events
    ofAddListener(mTimerBeforeHint.timerEnd, this,&scGame::timerBeforeHintEnd);
    ofAddListener(mTimerSignHint.timerEnd,   this,&scGame::timerSignHintEnd);
    ofAddListener(mTimerForceWin.timerEnd,   this,&scGame::timerForceWinEnd);
    
    // On ne refait pas ca si on vient de l'indice
    if(fromScreen->getSceneID() != HINT){
        // Restart a timer that we win anytime
        restartTimerForceWin();
        mNbHints = 0;
        petitTrain.restart();
//        mDrawPetitTrain = true;
    }else{
        // unPause the timer
        mTimerForceWin.resume();
        
        // reset indice nr
        hintUserId = 0;
        
    }
    
}

void scGame::sceneWillDisappear( ofxScene * toScreen ){
    // reset our scene when we appear
    scScene::sceneWillDisappear(toScreen);
    
    // On ne refait pas ca si on vient de l'indice
    if(toScreen->getSceneID() != HINT){
        // Restart a timer that we win anytime
        mTimerForceWin.stop();
        // Stop Drawing Train
//        mDrawPetitTrain = false;

    }else{
        // Pause the timer
        mTimerForceWin.pause();
    }
    mTimerBeforeHint.stop();
    
    // Reset all signs
    bigPlayerManager().stopSign(1);
    bigPlayerManager().stopSign(2);
    bigPlayerManager().stopSign(3);
    bigPlayerManager().stopSign(4);
    
    // Disable timer events
    ofRemoveListener(mTimerBeforeHint.timerEnd,  this,&scGame::timerBeforeHintEnd);
    ofRemoveListener(mTimerSignHint.timerEnd,    this,&scGame::timerSignHintEnd);
    ofRemoveListener(mTimerForceWin.timerEnd,    this,&scGame::timerForceWinEnd);

}
