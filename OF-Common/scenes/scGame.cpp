//
//  scGame.cpp
//  theBigGame
//
//  Created by Sébastien Albert on 06/06/2018.
//
//

#include "scGame.h"

void scGame::update(float dt){
    
    timerBeforeHint.update(dt);
    timerSignHint.update(dt);
    timerSignWin.update(dt);

    //    ofLogNotice() << "Temps avant indice : "  << timerBeforeHint.toString();
    //    ofLogNotice() << "Temps avant win : "  << timerSignWin.toString();

}

void scGame::someoneSpoke(player & _player){
    
    drawHintSign = false;
    
    scScene::someoneSpoke(_player);
    
    // Restart waiting timer
    restartTimerBeforeHint();
    // Stop eventually sign timer
    restartTimerSignHint();
    timerSignHint.stop();
}

void scGame::restartTimerSignHint(){
    ofLogNotice() << "Start timerSignHint, waiting..... ";
    timerSignHint.startTimer(5);
}
void scGame::restartTimerBeforeHint(){
    ofLogNotice() << "Start timerBeforeHint, waiting..... ";
    drawHintSign = false;
    timerBeforeHint.startTimer(30);
}
void scGame::restartTimerSignWin(){
    ofLogNotice() << "Start timerSignWin, waiting..... ";
    timerSignWin.startTimer(5);
}

void scGame::timerBeforeHintEnd(){
    
    ofLogNotice() << "fin du timer beforeHint, 5 seconds and go to hint";
    
    // --------------------------------
    drawHintSign = true;
    hintUserId = bigPlayerManager().getRandomPlayer();
    timerBeforeHint.stop();
    timerSignHint.startTimer(5);
}

void scGame::timerSignWinEnd(){
    
    ofLogNotice() << "fin du timer timerSignWin, go to scene 9 (WIN) ";
    // --------------------------------
    timerSignWin.stop();

}


void scGame::timerSignHintEnd(){
    
    ofLogNotice() << "fin du timer timerSignHint, go to scene (HINT) ";
    // --------------------------------
    timerSignHint.stop();
    ofxSceneManager::instance()->goToScene(HINT);
}

//scene notifications
void scGame::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);

    //signs
    drawWinnerSign = false;
    drawHintSign = false;
    
    restartTimerBeforeHint();
    
    // Player manager events
    ofAddListener(timerBeforeHint.timerEnd, this,&scGame::timerBeforeHintEnd);
    ofAddListener(timerSignHint.timerEnd,   this,&scGame::timerSignHintEnd);
    
}

void scGame::sceneWillDisappear( ofxScene * toScreen ){
    // reset our scene when we appear
    scScene::sceneWillDisappear(toScreen);
    
    // Disable timer events
    ofRemoveListener(timerBeforeHint.timerEnd,  this,&scGame::timerBeforeHintEnd);
    ofRemoveListener(timerSignHint.timerEnd,    this,&scGame::timerSignHintEnd);

}
