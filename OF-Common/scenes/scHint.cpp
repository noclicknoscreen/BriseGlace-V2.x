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
    
    //gui
    group.setName("Hint");
    group.add(lightPosX.set("lightPosX", 1600, -3000, 3000));
    group.add(lightPosY.set("lightPosY", 120, -3000, 3000));
    group.add(lightPosZ.set("lightPosZ", 0, -3000, 3000));
    
    group.add(orientationX.set("orientationX", 0, 0, 360));
    group.add(orientationY.set("orientationY", 0, 0, 360));
    group.add(orientationZ.set("orientationZ", 0, 0, 360));
    
    group.add(cutOff.set("cutOff", 0, 0, 180));
    group.add(concentration.set("concentration", 0, 0, 180));
    
    group.add(cubesRotationSpeed.set("cubesRotationSpeed", 5, 0.1, 20));
    
    gui.setup(group);
    gui.loadFromFile(settingsFileNameHint);

};


void scHint::update(float dt){ //update scene 1 here
    // Cube update
    myCubeManager.update(ofPoint(lightPosX, lightPosY, lightPosZ), ofPoint(orientationX, orientationY, orientationZ), cutOff, concentration, cubesRotationSpeed);
    
    mTimer.update(dt);
    timerBeforeRoll.update(dt);
    timerStartRoll.update(dt);
    
};

void scHint::draw(){ //draw scene 1 here
    
    //GUI
    if(bDrawGui){
        ofDisableLighting();
        gui.draw();
    }
    
    scScene::drawTitle("Voici l'indice.");
    
    // Draw cubes
    myCubeManager.draw();
    
    
};

//--------------------------------------------------------------
void scHint::keyPressed(int key){
    
    if(key=='l')
        myCubeManager.rotateToLetter(0);
    if(key=='w')
        myCubeManager.rotateToWood(0);
    if(key=='W')
        myCubeManager.rotateToWhite(0);
    if(key == 's') {
        gui.saveToFile(settingsFileNameGame2);
    }
    if(key == 'l') {
        gui.loadFromFile(settingsFileNameGame2);
    }
    if(key==' ' ){
        bDrawGui = !bDrawGui;
    }
}

//scene notifications
void scHint::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    from = fromScreen;
    
    //cubes
    myCubeManager.setup(ofPoint(0.5*ofGetWidth(), 0.5*ofGetHeight(), 0), 5, 100);
    currentCube = 0;
    
    // -- -- -- -- --
    timerBeforeRoll.startTimer(3);
    
    // Player manager events
    ofAddListener(mTimer.timerEnd, this, &scHint::timerEnd);
    ofAddListener(timerStartRoll.timerEnd, this, &scHint::timerStartRollEnd);
    ofAddListener(timerBeforeRoll.timerEnd, this, &scHint::timerBeforeRollEnd);
    ofAddListener(bigPlayerManager().someoneSpoke,this,&scHint::someoneSpoke);

};
void scHint::timerEnd(){
    // --------------------------------
    ofxSceneManager::instance()->goToScene(from->getSceneID());
}
void scHint::timerBeforeRollEnd(){
    
    ofLogNotice() << "End of timerBeforeRoll, start roll cubes";
    
    timerStartRoll.startTimer(0.5);
    timerBeforeRoll.stop();
}
void scHint::timerStartRollEnd(){
    
    ofLogNotice() << "End of timerStartRoll, will roll cube n°" << currentCube;
    
    // --------------------------------
    if(currentCube < myCubeManager.getNumberOfCubes()){
        myCubeManager.rotateToWood(currentCube);
        currentCube++;
        timerStartRoll.startTimer(0.5);
    }else{
        mTimer.startTimer(1);
        timerStartRoll.stop();
    }
}

//scene notifications
void scHint::sceneWillDisappear( ofxScene * toScreen ){
    ofRemoveListener(bigPlayerManager().someoneSpoke,this,&scHint::someoneSpoke);
}

// Events callback -----------------------------------
// Speaking event
void scHint::someoneSpoke(player & _player){
    // Waiting for a test (j'ai dit oui')
    // --------------------------------
    ofxSceneManager::instance()->goToScene(from->getSceneID());
}





