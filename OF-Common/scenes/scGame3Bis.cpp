//
//  scGame3Bis.cpp
//  theBigGame
//
//  Created by Sébastien Albert on 18/06/2018.
//
//

#include "scGame3Bis.h"

//--------------------------------------------------------------
void scGame3Bis::sceneWillAppear( ofxScene * fromScreen ){
    
    scGame::sceneWillAppear(fromScreen);
    spotLight.enable();
    
    //now comes from enigma Singleton
    wantedWord = utils::toWString(utils::toUpperCase(bigEnigmaManager().getCurrentEnigma()->getSolution()));
    
    for(int i=0; i<myCubes.size(); i++)
    {
        myCubes[i]->remove();
    }
    myCubes.clear();
    
    //physics
    setupPhysics(ofVec3f(2500.0, 1000.0, 1000.0));
    
    for(int i=0; i<wantedWord.size(); i++)
    {
        ofVec3f startPosition;
        startPosition.x = ofMap((float)i / (float)wantedWord.size(), 0, 1, -400, 400);
        startPosition.y = 550;
        startPosition.z = ofRandom(-5, 5);
        
        box = new cubeRigidBody();
        //            box->setup(texture, ofToString(wantedWord[wantedWord.size()-(i+1)]), 40);
        box->setup(texture, wantedWord.substr(i,1));
//        box->create(world.world, ofVec3f(0, 600, 0), .5, 80, 80, 80);
        box->create(world.world, startPosition, .5, 80, 80, 80);
        box->add();
        box->applyForce(START_FORCE_FACTOR_BIS*ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)), box->getPosition());

        
        myCubes.push_back(box);
    }
    
    // EVENTS
    // timer timeout
    mTimerEndScene.startTimer(5);
    // Listener
    ofAddListener(mTimerEndScene.timerEnd, this, &scGame3Bis::timerEndSceneEnd);
    
};

//--------------------------------------------------------------
void scGame3Bis::sceneWillDisappear( ofxScene * toScreen ){
    scGame::sceneWillDisappear(toScreen);
    
    // EVENTS
    ofRemoveListener(mTimerEndScene.timerEnd, this, &scGame3Bis::timerEndSceneEnd);
    
}


//--------------------------------------------------------------
void scGame3Bis::update(float dt){
    
    mTimerEndScene.update(dt);
    
    //light
    spotLight.setOrientation( ofVec3f( 0, 45, 30) );
    spotLight.setPosition(1600, 483,0);
    
    lightColor.setHue(0);
    spotLight.setDiffuseColor(lightColor);
    
    camera.setGlobalPosition(ofVec3f(camPosX, camPosY, camPosZ));
    world.setGravity(ofVec3f(0,gravity, 0));
    
    world.update();
    
    for(int i=0; i<myCubes.size(); i++)
    {
        myCubes[i]->setActivationState(1);
    }

    material.setSpecularColor(materialColor);
    
//    //display result for 10 seconds and go to winner screen
//    if(ofGetElapsedTimef() - timer > 5)
//    {
//        ofxSceneManager::instance()->goToScene(9);
//    }
    
    
    //materialColor = winnerColor;
    
};


//--------------------------------------------------------------
void scGame3Bis::draw(){
    
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    
    ofSetBackgroundColor(255);
    
    ofEnableLighting();
    ofSetSmoothLighting(true);
    
    material.setAmbientColor(materialColor);
    material.setDiffuseColor(materialColor);
    
    camera.begin();
    
#if defined DRAW_DEBUG
    ofSetColor(100, 100, 100);
    ofNoFill();
    ground.draw();
    rightFace.draw();
    leftFace.draw();
    bottom.draw();
    ofFill();
    
    spotLight.draw();
#endif
    
    material.begin();
    for(int i=0; i<myCubes.size(); i++)
    {
        myCubes[i]->customDraw(bigPlayerManager().getUserColor(bigPlayerManager().getWinnerUserId()));
        //            myCubes[i]->customDraw(ofColor::blueSteel);
    }
    material.end();
    ofDisableLighting();
    
#if defined DRAW_DEBUG
    world.drawDebug();
#endif
    
    camera.end();
    
    
    ofDisableDepthTest();
    
    if(bDrawGui)
        gui.draw();
    
    //ofDrawBitmapString("volume amount : " + ofToString(amount) + "NumberOfPlayers" + ofToString(bigPlayerManager().getNumberOfPlayers()), 100, 100);
    
    // Draw title
    scScene::drawTitle("Mot brassé");
    //scScene::drawSubTitle("Parlez dans l'oreille pour retourner les cubes");
    
    // Draw players
    bigPlayerManager().draw();
    
}

// EVENTS
void  scGame3Bis::timerEndSceneEnd(){
    ofxSceneManager::instance()->goToScene(VICTORY);
}

