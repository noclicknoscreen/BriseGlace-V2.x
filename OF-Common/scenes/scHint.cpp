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
    
    mTimerEndScene.update(dt);
    mTimerBeforeRoll.update(dt);
    mTimerStartRoll.update(dt);
    
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
    mTimerBeforeRoll.startTimer(3);
    
    // events ---
    ofAddListener(mTimerEndScene.timerEnd, this, &scHint::timerEndScene);
    ofAddListener(mTimerStartRoll.timerEnd, this, &scHint::timerStartRollEnd);
    ofAddListener(mTimerBeforeRoll.timerEnd, this, &scHint::timerBeforeRollEnd);
    ofAddListener(bigPlayerManager().someoneSpoke,this,&scHint::someoneSpoke);

}

void scHint::sceneWillDisappear( ofxScene * toScreen){
    scScene::sceneWillDisappear(toScreen);
    
    mTimerStartRoll.stop();
    mTimerBeforeRoll.stop();
    mTimerEndScene.stop();
    
    // events ---
    ofRemoveListener(mTimerEndScene.timerEnd, this, &scHint::timerEndScene);
    ofRemoveListener(mTimerStartRoll.timerEnd, this, &scHint::timerStartRollEnd);
    ofRemoveListener(mTimerBeforeRoll.timerEnd, this, &scHint::timerBeforeRollEnd);
    ofRemoveListener(bigPlayerManager().someoneSpoke,this,&scHint::someoneSpoke);
    
}

// EVENTS ////////////////////////////////////////////////////////////////////////////////////////////
// Speaking event
void scHint::someoneSpoke(player & _player){
    // Waiting for a test (j'ai dit oui')
    // --------------------------------
    ofxSceneManager::instance()->goToScene(from->getSceneID());
}
void scHint::timerEndScene(){
    // --------------------------------
    ofxSceneManager::instance()->goToScene(from->getSceneID());
}
void scHint::timerBeforeRollEnd(){
    
    ofLogNotice() << "End of timerBeforeRoll, start roll cubes";
    
    mTimerStartRoll.startTimer(0.5);
    mTimerBeforeRoll.stop();
}
void scHint::timerStartRollEnd(){
    
    ofLogNotice() << "End of timerStartRoll, will roll cube n°" << currentCube;
    
    // --------------------------------
    if(currentCube < myCubeManager.getNumberOfCubes()){
        myCubeManager.rotateToWood(currentCube);
        currentCube++;
        mTimerStartRoll.startTimer(0.5);
    }else{
        mTimerEndScene.startTimer(1);
        mTimerStartRoll.stop();
    }
}






