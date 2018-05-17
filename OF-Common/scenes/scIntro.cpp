//
//  scIntro.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scIntro.h"



void scIntro::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Introduction : Setup !";
};


void scIntro::update(float dt){ //update scene 1 here
};

void scIntro::draw(){ //draw scene 1 here
    scScene::drawTitle("Vous êtes joueur ? \nNous oui !");
};

//scene notifications
void scIntro::sceneWillAppear( ofxScene * fromScreen ){
    scScene::sceneWillAppear(fromScreen);
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke,this,&scIntro::someoneSpoke);
};

//scene notifications
void scIntro::sceneWillDisappear( ofxScene * toScreen ){
    // Player manager events
    ofRemoveListener(bigPlayerManager().someoneSpoke,this,&scIntro::someoneSpoke);
}

// Speaking event
void scIntro::someoneSpoke(player & _player){
    ofxSceneManager::instance()->goToScene(SELECT_GAME);
}


