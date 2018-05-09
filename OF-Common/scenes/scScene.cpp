//
//  scScene.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 08/05/2018.
//
//

#include "scScene.h"

// Constructor
scScene::scScene(ofEvent<void> _endSceneEvent, playerManager &_manager){
    endSceneEvent = _endSceneEvent;
    myPlayerManager = &_manager;
}

void scScene::setup(){
    myFont24.load("Folktale.ttf", 24, true, true);
}

void scScene::draw(){
    // Draw title
    drawCenterText(myTitle);
}


void scScene::drawCenterText(string _message, int _plusX, int _plusY){
    ofPushMatrix();
    ofRectangle bounds = myFont24.getStringBoundingBox(_message, 0, 0);
    ofTranslate(0.5 * (ofGetWidth() - bounds.width) + _plusX, 0.5 * (ofGetHeight() - bounds.height) + _plusY);
    myFont24.drawString(_message, 0, 0);
    ofPopMatrix();
}

void scScene::someoneSpoke(player & _player){
    ofLogNotice() << "[Scene " << getSceneID()<< "] SomeOne Spoke : " << _player.getNumber() << ":" << _player.getLastMessage();
}
