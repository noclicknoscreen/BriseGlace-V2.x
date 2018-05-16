//
//  scHint.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scHint.h"

void scHint::setup(){  //load your scene 1 assets here...
    
    scScene::setup();
    ofLogNotice() << "Indice : Setup !";
    myTitle = "Ecran d'indices";
    

};


void scHint::update(float dt){ //update scene 1 here
    
    myIndice.update();
    
    if(ofGetElapsedTimef() - timer > 5)
        myIndice.setRevealMode();
    
};

void scHint::draw(){ //draw scene 1 here
    
    ofEnableDepthTest();
    myIndice.draw();
    
    // Draw Timer
    myText.setText(utils::toUpperCase("Voici l'indice."));
    myText.drawCenter(0.5 * ofGetWidth(), 0.25 * ofGetHeight());
    
    
};

//scene notifications
void scHint::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    
    myIndice.setup(bigEnigmaManager().getCurrentEnigma());
    
    timer = ofGetElapsedTimef();
    
    // -- -- -- -- --
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke,this,&scHint::someoneSpoke);

};

//scene notifications
void scHint::sceneWillDisappear( ofxScene * toScreen ){
    ofRemoveListener(bigPlayerManager().someoneSpoke,this,&scHint::someoneSpoke);
}

// Events callback -----------------------------------
// Speaking event
void scHint::someoneSpoke(player & _player){
    // Waiting for a test (j'ai dit oui')
    // --------------------------------
    ofxSceneManager::instance()->goToScene(GAME1);
}





