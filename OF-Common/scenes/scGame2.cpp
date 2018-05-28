//
//  scGame2.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame2.h"

void scGame2::setup(){
    
    scScene::setup();
    ofLogNotice() << "Game 2 : Setup !";

    //cubes
    myCubeManager.setup();

    //word to find
    myCubeManager.getWord("Mes mots rient");
    
    //gui

    gui.setup();
    gui.add(lightPosX.set("lightPosX", 1600, -1000, ofGetWidth()*2));
    gui.add(lightPosY.set("lightPosY", 120, -1000, 1000));
    gui.add(lightPosZ.set("lightPosZ", 0, -100, 100));
    gui.add(cubesRotationSpeed.set("cubesRotationSpeed", 5, 0.1, 20));
    
    bDrawGui=false;
    
};



void scGame2::update(float dt){
    
    myCubeManager.update(ofPoint(lightPosX, lightPosY, lightPosZ), cubesRotationSpeed);
    
};

void scGame2::draw(){ //draw scene 1 here
    
    // Draw cubes
    ofPushStyle();
    ofPushMatrix();
    
        //myCubeManager.draw();
        
        ofDisableLighting();
        ofDisableDepthTest();
        ofSetColor(255);
        //GUI
        if(bDrawGui)
            gui.draw();
    
    ofPopStyle();
    ofPopMatrix();
    
    // Draw Title
    scScene::drawTitle("Mes mots rient");
    scScene::drawSubTitle("Prochainement dans votre gare...");
    
    // Draw players
    bigPlayerManager().draw();
    
};

//scene notifications
void scGame2::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    
    // Erase all words of every one
    bigPlayerManager().freshRestart();
    
    // On ne refait pas ca si on vient de l'indice
    if(fromScreen->getSceneID() != HINT){
        // Load the next enigma
        bigEnigmaManager().pickNewEnigma(MOTUS);
        
        //cubes
        myCubeManager.setup();
        myCubeManager.getWord("Mes mots rient");
        
    }

};

//scene notifications
void scGame2::sceneWillDisappear( ofxScene * toScreen ){
}
