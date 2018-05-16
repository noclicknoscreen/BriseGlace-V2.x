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
    
    
    //cubes
    myCubeManager.setup();
    
    //inputs
    myInputManager.setup();
    
    //word to find
    myCubeManager.getWord(bigEnigmaManager().getCurrentEnigma()->getSolution());
    myInputManager.clearDuplicatesLettersHistory();
    myInputManager.setReadyForNewText();
    myInputManager.setWordToFind(bigEnigmaManager().getCurrentEnigma()->getSolution());
    

    //gui
    bDrawGui=false;
    
};

void scGame1::update(float dt){ //update scene 1 here
    
    myCubeManager.update(ofPoint(lightPosX, lightPosY, lightPosZ), cubesRotationSpeed);
    myInputManager.update(&myCubeManager);

    mTimer.update(dt);
    
};

void scGame1::draw(){ //draw scene 1 here
    
    ofPushStyle();
        ofPushMatrix();
        
            myCubeManager.draw();
            myInputManager.draw();
            
            ofDisableLighting();
            ofDisableDepthTest();
            ofSetColor(255);
            //GUI
            if(bDrawGui)
                gui.draw();
        ofPopStyle();
    ofPopMatrix();
    

    ofPushStyle();
 
        ofSetColor(ofColor(255,0,0));
    
    //debug
    //    ofDrawCircle(200, 200, 200);
        
        scScene::draw();            // Draw title
        bigPlayerManager().draw();    // Draw players

    ofPopStyle();
    
    // Draw Timer
    myText.setText(utils::toUpperCase("Il vous reste " + mTimer.toString() + " secondes avant l'indice."));
    myText.drawCenter(0.5 * ofGetWidth(), 0.55 * ofGetHeight());

};

//--------------------------------------------------------------
void scGame1::keyPressed(int key){
    
    if(key=='l')
        myCubeManager.rotateToLetter(0);
    if(key=='w')
        myCubeManager.rotateToWood(0);
    if(key=='W')
        myCubeManager.rotateToWhite(0);
    if(key==' ' )
        bDrawGui = !bDrawGui;
    
}

//scene notifications
void scGame1::sceneWillAppear( ofxScene * fromScreen ){
    
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke,this,&scGame1::someoneSpoke);
    // Load the next enigma
    bigEnigmaManager().pickNewEnigma(MOTUS);
    
    gui.setup();
    //gui.add
    gui.add(lightPosX.set("lightPosX", 1600, -1000, ofGetWidth()*2));
    gui.add(lightPosY.set("lightPosY", 120, -1000, 1000));
    gui.add(lightPosZ.set("lightPosZ", 0, -100, 100));
    gui.add(cubesRotationSpeed.set("cubesRotationSpeed", 5, 0.1, 20));
    
    // On ne refiat pas ca si on vient de l'indice
    if(fromScreen->getSceneID() != HINT){
        //cubes
        myCubeManager.setup();
        
        //inputs
        myInputManager.setup();
        
        //TODO :: bonheur ecrit en dur => lu dans le JSON
        myCubeManager.getWord(bigEnigmaManager().getCurrentEnigma()->getSolution());
        myInputManager.clearDuplicatesLettersHistory();
        myInputManager.setReadyForNewText();
        myInputManager.setWordToFind(utils::toUpperCase(bigEnigmaManager().getCurrentEnigma()->getSolution()));
    }
    
    // -- -- -- -- --
    mTimer.startTimer(45);
    // Player manager events
    ofAddListener(mTimer.timerEnd,this,&scGame1::timerEnd);

};

//scene notifications
void scGame1::sceneWillDisappear( ofxScene * toScreen ){
    // Player manager events
    ofRemoveListener(bigPlayerManager().someoneSpoke,this,&scGame1::someoneSpoke);
    ofRemoveListener(mTimer.timerEnd,this,&scGame1::timerEnd);
}

// Events callback -----------------------------------
// Speaking event
void scGame1::someoneSpoke(player & _player){
    scScene::someoneSpoke(_player);
    
    if(myInputManager.isReadyForNewText())
        myInputManager.getNewText(_player);
    
    
    mTimer.startTimer(45);
    
}
void scGame1::timerEnd(){
    // --------------------------------
    ofxSceneManager::instance()->goToScene(HINT);
}

