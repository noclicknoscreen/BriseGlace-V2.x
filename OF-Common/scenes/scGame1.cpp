//
//  scGame1.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame1.h"

void scGame1::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Game 1 : Setup !";
    myTitle = "Game 1 : Mot caché";
    
    
    gui.setup();
    //gui.add
    gui.add(lightPosX.set("lightPosX", 850, -1000, 1000));
    gui.add(lightPosY.set("lightPosY", 120, -1000, 1000));
    gui.add(lightPosZ.set("lightPosZ", 0, -100, 100));
    gui.add(cubesRotationSpeed.set("cubesRotationSpeed", 5, 0.1, 20));
    
    //cubes
    myCubeManager.setup();
    
    //inputs
    myInputManager.setup();
    
    // Player manager events
    ofAddListener(myPlayerManager->someoneSpoke,this,&scGame1::someoneSpoke);
    
};

void scGame1::update(float dt){ //update scene 1 here
    
    myCubeManager.update(ofPoint(lightPosX, lightPosY, lightPosZ), cubesRotationSpeed);
    myInputManager.update(&myCubeManager);
    
};

void scGame1::draw(){ //draw scene 1 here
    
    myCubeManager.draw();
    myInputManager.draw();
    
    ofDisableLighting();
    ofDisableDepthTest();
    ofSetColor(255);
    gui.draw();
    
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::red);
    
    ofDrawBitmapString(bigEnigmaManager().getEnigmaName(), 0.5 * ofGetWidth(), 0.5 * ofGetHeight());
    
    scScene::draw();            // Draw title
    myPlayerManager->draw();    // Draw players
    //drawCenterText(myPlayerManager->getLastMessage(), 0, 50); // Draw last message

    ofPopStyle();
    
};

//--------------------------------------------------------------
void scGame1::keyPressed(int key){
    
    if(key=='l')
        myCubeManager.rotateToLetter(0);
    if(key=='w')
        myCubeManager.rotateToWood(0);
    if(key=='W')
        myCubeManager.rotateToWhite(0);
    
    if(key==' ')
    {
        myCubeManager.getWord("bonheur");
        myInputManager.clearDuplicatesLettersHistory();
    }
    
    if(key=='p')
    {
        myInputManager.getNewText(1, "choucroute");
    }
    
    if(key=='P')
    {
        myInputManager.getNewText(1, "bonnet");
    }
    
    if(key=='c')
    {
        myInputManager.compareInput("bonheur");
    }
    
    if(key == 'C')
    {
        //myInputManager.rotateCorrespondingCubes("bonheur", &myCubeManager);
        myInputManager.setRevealMode();
    }
    
}

// Speaking event
void scGame1::someoneSpoke(player & _player){
    scScene::someoneSpoke(_player);
    
    myInputManager.getNewText(_player.getNumber(), _player.getLastMessage());
    
}

//scene notifications
void scGame1::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
};

//scene notifications
void scGame1::sceneWillDisappear( ofxScene * toScreen ){
}
