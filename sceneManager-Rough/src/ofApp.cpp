#include "ofApp.h"


void ofApp::setup(){

	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
    ofBackground(ofColor::white);
	ofEnableSmoothing();
		
	///////////////////////////////////////
	
	sceneManager = ofxSceneManager::instance();
    sceneManager->setupCurtain(ofColor::white, ofRectangle(0,0, ofGetWidth(), ofGetHeight()) );
    sceneManager->addScene( new scIntro(), INTRO);
    sceneManager->addScene( new scInitialize(), INITIALIZE);
    sceneManager->addScene( new scSelectGame(), SELECT_GAME);
    sceneManager->addScene( new scGame1(), GAME1);
    sceneManager->addScene( new scGame2(), GAME2);
    sceneManager->addScene( new scGame3(), GAME3);
    sceneManager->addScene( new scHint(), HINT);
    sceneManager->addScene( new scVictory(), VICTORY);
    
	sceneManager->setDrawDebug(true);
	sceneManager->setCurtainDropTime(1.0);
	sceneManager->setCurtainStayTime(0.0);
	sceneManager->setCurtainRiseTime(1.0);
	sceneManager->setOverlapUpdate(true);
}

void ofApp::update(){
	
	float dt = 0.016666666;
	sceneManager->update( dt );
		
}


void ofApp::draw(){

	sceneManager->draw();
	
	ofSetColor(255,0,0);
	ofDrawBitmapString( "press 1, 2, or 3 to change scene", ofGetWidth() - 290, ofGetHeight() - 10);	
}


//if you require mouseMoved events in your scenes, forward them to the SceneManager. Same for any other events
void ofApp::mousePressed( int x, int y, int button ){
	sceneManager->mousePressed(x, y, button);
}

void ofApp::keyPressed(int key){
	
    if (key == '1') sceneManager->goToScene(INTRO);
    if (key == '2') sceneManager->goToScene(INITIALIZE);
    if (key == '3') sceneManager->goToScene(SELECT_GAME);
    if (key == '4') sceneManager->goToScene(GAME1);
    if (key == '5') sceneManager->goToScene(GAME2);
    if (key == '6') sceneManager->goToScene(GAME3);
    if (key == '7') sceneManager->goToScene(HINT);
    if (key == '8') sceneManager->goToScene(VICTORY);
    
    if (key == OF_KEY_RIGHT || key == OF_KEY_LEFT){
        int scId = sceneManager->getCurrentSceneID();
        if (key == OF_KEY_RIGHT){
            if(scId == sceneManager->getNumScenes()){
                scId = 1;
            }else{
                scId++;
            }
        }
        if (key == OF_KEY_LEFT){
            if(scId == 1){
                scId = sceneManager->getNumScenes();
            }else{
                scId--;
            }
        }
        sceneManager->goToScene(scId);
    }
    
    
}


void ofApp::windowResized(int w, int h){
	sceneManager->windowResized(w,h); // in case your screens need to know, will forward to all of them
}
