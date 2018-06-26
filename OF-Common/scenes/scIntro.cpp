//
//  scIntro.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scIntro.h"

#define timerTexteDuration 2

void scIntro::setup(){  //load your scene 1 assets here...
    scScene::setup();
    
//    mTimerTexte.startTimer(10);
//    mTimerTexte.stop();
    
    ofLogNotice() << "Introduction : Setup !";
};


void scIntro::update(float dt){
    scSelect::update(dt);
//    mTimerTexte.update(dt);
};

void scIntro::draw(){ //draw scene 1 here
    scScene::drawTitle("Bienvenue sur \"Jeux de mô\"", ofColor::black, ofPoint(0, 150));
    scScene::drawSubTitle("Aidez-nous à retrouver nos mots perdus", ofColor::black, ofPoint(0, 375));
    scScene::drawSubTitle("en nous parlant dans l'oreille.", ofColor::black, ofPoint(0, 440));
//    if(bDrawSubtitle1==true){
//        scScene::drawFullCenterLine2("Moi oui !", ofColor::black, ofPoint(0,-100));
//    }
//    if(bDrawSubtitle2==true){
//        scScene::drawFullCenterLine3("Parlez-moi dans l'oreille.", ofColor::black, ofPoint(0,-75));
//    }
    
    bigPlayerManager().draw();
    
};

//scene notifications
void scIntro::sceneWillAppear( ofxScene * fromScreen ){
    scSelect::sceneWillAppear(fromScreen);
    mPlayerMessage = "";
    
//    mTimerTexte.startTimer(timerTexteDuration);
//    
//    bDrawSubtitle1 = false;
//    bDrawSubtitle2 = false;
    
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke   ,this,&scIntro::someoneSpoke);
    ofAddListener(mTimerSignAnimation.timerEnd      ,this,&scIntro::timerSignAnimationEnd);
//    ofAddListener(mTimerTexte.timerEnd              ,this,&scIntro::timerTexteEnd);
};

//scene notifications
void scIntro::sceneWillDisappear( ofxScene * toScreen ){
    scSelect::sceneWillDisappear(toScreen);
    
    // Player manager events
    ofRemoveListener(bigPlayerManager().someoneSpoke    ,this,&scIntro::someoneSpoke);
    ofRemoveListener(mTimerSignAnimation.timerEnd       ,this,&scIntro::timerSignAnimationEnd);
//    ofRemoveListener(mTimerTexte.timerEnd               ,this,&scIntro::timerTexteEnd);
    
}

// EVENTS ////////////////////////////////////////////////////////////////////////////////////////////
// Speaking event
void scIntro::someoneSpoke(player & _player){
    scSelect::someoneSpoke(_player);
    ofxSceneManager::instance()->goToScene(SELECT_GAME);
}

//// Timer event
//void  scIntro::timerTexteEnd(){
//    
//    if(bDrawSubtitle1==false){
//        mTimerTexte.startTimer(timerTexteDuration);
//        bDrawSubtitle1 = true;
//    }else{
//        if(bDrawSubtitle2==false){
//            mTimerTexte.stop();
//            bDrawSubtitle2 = true;
//        }
//    }
//}

void scIntro::timerSignAnimationEnd(){
    
    string signMessage;
    
    mTimerSignAnimation.startTimer(2 + ofRandom(-1, 1));
    bigPlayerManager().stopSign(numPlayer);
    
    numPlayer++;
    if(numPlayer>3){
        numPlayer = 1;
    }
    
    // Draw players
    switch (numPlayer) {
        case 1:
            signMessage = "Moi, c'est MOT BLEU";
            break;
        case 2:
            signMessage = "Moi, c'est ROUGE MOT";
            break;
        case 3:
            signMessage = "Moi, c'est MOT MAUVE";
            break;
            
        default:
            break;
    }
    
    bigPlayerManager().startSign(numPlayer, signMessage);
    
}


