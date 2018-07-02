//
//  scScene.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 08/05/2018.
//
//

#include "scSelect.h"

//// Constructor
//scScene::scScene(playerManager &_manager){
//    myPlayerManager = &_manager;
//}

void scSelect::update(float dt){
    mTimerSignAnimation.update(dt);
};

// Speaking event
void scSelect::someoneSpoke(player & _player){
    
    scScene::someoneSpoke(_player);
    
    mPlayerMessage = _player.getLastMessage();
    mPlayerColor = _player.getColor();
//    mTimerEraseWord.startTimer(2);
    
    ofLogNotice() << "Last spoken word is : " << _player.getLastMessage();
    // Choix du jeu 1 : Mot Masqué
    if(ofStringTimesInString(mPlayerMessage, "masqu") > 0){
        ofxSceneManager::instance()->goToScene(GAME1);
    }
    if(ofStringTimesInString(mPlayerMessage, "cach") > 0){
        ofxSceneManager::instance()->goToScene(GAME1);
    }
//    if(ofStringTimesInString(mPlayerMessage, "masqué") > 0){
//        ofxSceneManager::instance()->goToScene(GAME1);
//    }
//    if(ofStringTimesInString(mPlayerMessage, "masquer") > 0){
//        ofxSceneManager::instance()->goToScene(GAME1);
//    }
//    if(ofStringTimesInString(mPlayerMessage, "caché") > 0){
//        ofxSceneManager::instance()->goToScene(GAME1);
//    }
//    if(ofStringTimesInString(mPlayerMessage, "cacher") > 0){
//        ofxSceneManager::instance()->goToScene(GAME1);
//    }
    
    // Choix du jeu 2 : Mes mots rient
    if(ofStringTimesInString(mPlayerMessage, "rient") > 0){
        ofxSceneManager::instance()->goToScene(GAME2);
    }
    if(ofStringTimesInString(mPlayerMessage, "riz") > 0){
        ofxSceneManager::instance()->goToScene(GAME2);
    }
    if(ofStringTimesInString(mPlayerMessage, "memory") > 0){
        ofxSceneManager::instance()->goToScene(GAME2);
    }
    if(ofStringTimesInString(mPlayerMessage, "memories") > 0){
        ofxSceneManager::instance()->goToScene(GAME2);
    }
    
    // Choix du jeu 3 : Mot Brassé
    if(ofStringTimesInString(mPlayerMessage, "brass") > 0){
        ofxSceneManager::instance()->goToScene(GAME3);
    }
//    if(ofStringTimesInString(mPlayerMessage, "brasser") > 0){
//        ofxSceneManager::instance()->goToScene(GAME3);
//    }
    if(ofStringTimesInString(mPlayerMessage, "bracelet") > 0){
        ofxSceneManager::instance()->goToScene(GAME3);
    }
    
    if(ofStringTimesInString(mPlayerMessage, "n'importe quoi") > 0){
        int rndIdx = ofRandom(0, 3);
        if(rndIdx <  1){
            ofxSceneManager::instance()->goToScene(GAME1);
        }else if(rndIdx <  2){
            ofxSceneManager::instance()->goToScene(GAME2);
        }else if(rndIdx <  3){
            ofxSceneManager::instance()->goToScene(GAME3);
        }
    }
    
    if(ofStringTimesInString(mPlayerMessage, "partenaire") > 0){
        ofxSceneManager::instance()->goToScene(PARTNERS);
    }
    
}


//void scSelect::timerEraseWordEnd(){
//    //ofLogNotice() << "Erase word to avoid bullshits";
//    mPlayerMessage = "";
////    mTimerEraseWord.stop();
//}

//scene notifications
void scSelect::sceneWillAppear( ofxScene * fromScreen ){
    
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    mPlayerMessage = "";
    
    // Erase all words of every one
    mTimerSignAnimation.startTimer(2);
//    mTimerEraseWord.startTimer(2);
    
    // Player manager events
//    ofAddListener(bigPlayerManager().someoneSpoke   ,this,&scSelect::someoneSpoke);
//    ofAddListener(mTimerSignAnimation.timerEnd      ,this,&scSelect::timerSignAnimationEnd);
//    ofAddListener(mTimerEraseWord.timerEnd      ,this,&scSelect::timerEraseWordEnd);
};

//scene notifications
void scSelect::sceneWillDisappear( ofxScene * toScreen ){
    // reset our scene when we appear
    scScene::sceneWillDisappear(toScreen);
    
    // Player manager events
//    ofRemoveListener(bigPlayerManager().someoneSpoke    ,this,&scSelect::someoneSpoke);
//    ofRemoveListener(mTimerSignAnimation.timerEnd       ,this,&scSelect::timerSignAnimationEnd);
//    ofRemoveListener(mTimerEraseWord.timerEnd           ,this,&scSelect::timerEraseWordEnd);
}
