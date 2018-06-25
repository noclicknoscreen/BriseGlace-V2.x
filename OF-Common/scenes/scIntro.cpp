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
    
    mTimerTexte.startTimer(10);
    mTimerTexte.stop();
    
    ofLogNotice() << "Introduction : Setup !";
};


void scIntro::update(float dt){
    mTimerTexte.update(dt);
};

void scIntro::draw(){ //draw scene 1 here
    scScene::drawFullCenterLine1("Vous êtes joueur ?", ofColor::black, ofPoint(0,-100));
    if(bDrawSubtitle1==true){
        scScene::drawFullCenterLine2("Moi oui !", ofColor::black, ofPoint(0,-100));
    }
    if(bDrawSubtitle2==true){
        scScene::drawFullCenterLine3("Parlez-moi dans l'oreille.", ofColor::black, ofPoint(0,-75));
    }
    
    bigPlayerManager().draw();
    
};

//scene notifications
void scIntro::sceneWillAppear( ofxScene * fromScreen ){
    scScene::sceneWillAppear(fromScreen);
    
    mTimerTexte.startTimer(timerTexteDuration);
    
    bDrawSubtitle1 = false;
    bDrawSubtitle2 = false;
    
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke   ,this,&scIntro::someoneSpoke);
    ofAddListener(mTimerTexte.timerEnd              ,this,&scIntro::timerTexteEnd);
};

//scene notifications
void scIntro::sceneWillDisappear( ofxScene * toScreen ){
    scScene::sceneWillDisappear(toScreen);
    
    // Player manager events
    ofRemoveListener(bigPlayerManager().someoneSpoke    ,this,&scIntro::someoneSpoke);
    ofRemoveListener(mTimerTexte.timerEnd               ,this,&scIntro::timerTexteEnd);
    
}

// EVENTS ////////////////////////////////////////////////////////////////////////////////////////////
// Speaking event
void scIntro::someoneSpoke(player & _player){
    scSelect::someoneSpoke(_player);
    ofxSceneManager::instance()->goToScene(SELECT_GAME);
}

// Timer event
void  scIntro::timerTexteEnd(){
    
    if(bDrawSubtitle1==false){
        mTimerTexte.startTimer(timerTexteDuration);
        bDrawSubtitle1 = true;
    }else{
        if(bDrawSubtitle2==false){
            mTimerTexte.stop();
            bDrawSubtitle2 = true;
        }
    }
}

