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
    myTextTitle.init(globalFontName, globalFontSizeBig);
    myTextTitle.setColor(0, 0, 0, 0);
    // Set the texts
    myTextSubTitle.init(globalFontName, globalFontSizeMedium);
    myTextSubTitle.setColor(0, 0, 0, 0);
    //
    myTextSpokenWord.init(globalFontName, globalFontSizeSmall);
    myTextSpokenWord.setColor(0, 0, 0, 0);
}

void scScene::update(float dt){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

void scScene::drawTitle(string _text, ofColor _color, ofPoint _correc){
    // Draw title
    myTextTitle.setText(utils::toUpperCase(_text));
    myTextTitle.wrapTextX(0.7 * ofGetWidth());
    myTextTitle.setColor(_color.r, _color.g, _color.b, _color.a);
    myTextTitle.drawCenter(0.5 * ofGetWidth() + _correc.x, 0.05 * ofGetHeight() + _correc.y);
}

void scScene::drawSubTitle(string _text, ofColor _color, ofPoint _correc){
    // Draw title
    myTextSubTitle.setText(utils::toUpperCase(_text));
    myTextSubTitle.wrapTextX(0.7 * ofGetWidth());
    myTextSubTitle.setColor(_color.r, _color.g, _color.b, _color.a);
    myTextSubTitle.drawCenter(0.5 * ofGetWidth() + _correc.x, 0.15 * ofGetHeight() + _correc.y);
}

void scScene::drawFullCenterLine1(string _text, ofColor _color, ofPoint _correc){
    // Draw title
    myTextTitle.setText(utils::toUpperCase(_text));
    myTextTitle.wrapTextX(0.7 * ofGetWidth());
    myTextTitle.setColor(_color.r, _color.g, _color.b, _color.a);
    myTextTitle.drawCenter(0.5 * ofGetWidth() + _correc.x, 0.5 * ofGetHeight() - 50 + _correc.y);
}

void scScene::drawFullCenterLine2(string _text, ofColor _color, ofPoint _correc){
    // Draw title
    myTextTitle.setText(utils::toUpperCase(_text));
    myTextTitle.wrapTextX(0.7 * ofGetWidth());
    myTextTitle.setColor(_color.r, _color.g, _color.b, _color.a);
    myTextTitle.drawCenter(0.5 * ofGetWidth() + _correc.x, 0.5 * ofGetHeight() + 50 + _correc.y);
}

void scScene::drawFullCenterLine3(string _text, ofColor _color, ofPoint _correc){
    // Draw title
    myTextSubTitle.setText(utils::toUpperCase(_text));
    myTextSubTitle.wrapTextX(0.7 * ofGetWidth());
    myTextSubTitle.setColor(_color.r, _color.g, _color.b, _color.a);
    myTextSubTitle.drawCenter(0.5 * ofGetWidth() + _correc.x, 0.5 * ofGetHeight() + 150 + _correc.y);
}

void scScene::drawSpokenWord(string _text, ofColor _color, ofPoint _correc){
    // Draw title
    myTextSpokenWord.setText(utils::toUpperCase(_text));
    myTextSpokenWord.wrapTextX(0.7 * ofGetWidth());
    myTextSpokenWord.setColor(_color.r, _color.g, _color.b, _color.a);
    myTextSpokenWord.drawCenter(0.5 * ofGetWidth() + _correc.x, 0.55 * ofGetHeight() + _correc.y);
}

void scScene::someoneSpoke(player & _player){
    ofLogNotice() << "[Scene " << getSceneID()<< "] SomeOne Spoke : " << _player.getNumber() << ":" << _player.getLastMessage();
}

void scScene::sceneWillAppear( ofxScene * fromScreen ){
    bigPlayerManager().freshRestart();
}

void scScene::sceneWillDisappear( ofxScene * toScreen ){
}
