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
    // Set the texts
    myTextTitle.init(globalFontName, globalFontSize);
    myTextTitle.setColor(0, 0, 0, 0);
    //
    myTextSpokenWord.init(globalFontName, globalFontSize);
    myTextSpokenWord.setColor(0, 0, 0, 0);
}

void scScene::update(float dt){
//    mTimer.update(dt);
}

void scScene::drawTitle(string _title, ofColor _color){
    // Draw title
    myTextTitle.setText(utils::toUpperCase(_title));
    myTextTitle.setColor(_color.r, _color.g, _color.b, _color.a);
    myTextTitle.drawCenter(0.5 * ofGetWidth(), 0.25 * ofGetHeight());
}

void scScene::drawSpokenWord(string _spokenWord, ofColor _color){
    // Draw title
    myTextSpokenWord.setText(utils::toUpperCase(_spokenWord));
    myTextSpokenWord.wrapTextX(0.7 * ofGetWidth());
    myTextSpokenWord.setColor(_color.r, _color.g, _color.b, _color.a);
    myTextSpokenWord.drawCenter(0.5 * ofGetWidth(), 0.65 * ofGetHeight());
}

void scScene::someoneSpoke(player & _player){
    ofLogNotice() << "[Scene " << getSceneID()<< "] SomeOne Spoke : " << _player.getNumber() << ":" << _player.getLastMessage();
}

void scScene::sceneWillAppear( ofxScene * fromScreen ){
    bigPlayerManager().freshRestart();
}

void scScene::sceneWillDisappear( ofxScene * fromScreen ){
}
