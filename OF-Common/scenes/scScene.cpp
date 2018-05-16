//
//  scScene.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 08/05/2018.
//
//

#include "scScene.h"

//// Constructor
//scScene::scScene(playerManager &_manager){
//    myPlayerManager = &_manager;
//}

void scScene::setup(){
    // Set the text
    myText.init(globalFontName, 24);
}

void scScene::draw(){
    // Draw title
    myText.setText(utils::toUpperCase(myTitle));
    myText.drawCenter(0.5 * ofGetWidth(), 0.5 * ofGetHeight());
}


void scScene::someoneSpoke(player & _player){
    ofLogNotice() << "[Scene " << getSceneID()<< "] SomeOne Spoke : " << _player.getNumber() << ":" << _player.getLastMessage();
}

void scScene::sceneWillAppear( ofxScene * fromScreen ){
//    myPlayerManager->freshRestart();
    bigPlayerManager().freshRestart();
}
void scScene::sceneWillDisappear( ofxScene * fromScreen ){
    
}
