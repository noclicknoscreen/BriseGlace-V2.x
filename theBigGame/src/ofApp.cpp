#include "ofApp.h"


void ofApp::setup(){

	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
    ofBackground(ofColor::white);
	ofEnableSmoothing();
		
    ///////////////////////////////////////
    myFont.load("Folktale.ttf", 28, true, true);
    
	///////////////////////////////////////
    // add the newFloat method to listen for eventsAddon newFloatEvent
    ofAddListener(nextSceneEvent,this,&ofApp::nextSceneAuto);
//    ofAddListener(bigPlayerManager().someoneSpoke,this,&ofApp::someoneSpoke);

    ///////////////////////////////////////
    bigPlayerManager().setup();
    
    /////////////////////////////////////
    bigEnigmaManager().setup();
    
    ///////////////////////////////////////
	sceneManager = ofxSceneManager::instance();
    sceneManager->setupCurtain(ofColor::white, ofRectangle(0,0, ofGetWidth(), ofGetHeight()) );
    
    sceneManager->addScene( new scIntro(), INTRO);
    sceneManager->addScene( new scInitialize(), INITIALIZE);
    sceneManager->addScene( new scSelectGame(), SELECT_GAME);
    sceneManager->addScene( new scGame1(), GAME1);
    sceneManager->addScene( new scGame2(), GAME2);
    sceneManager->addScene( new scGame3(), GAME3);
    sceneManager->addScene( new scGame3BIS(), GAME3_BIS);
    sceneManager->addScene( new scHint(), HINT);
    sceneManager->addScene( new scVictory(), VICTORY);
//    
//    sceneManager->addScene( new scIntro(myPlayerManager), INTRO);
//    sceneManager->addScene( new scInitialize(myPlayerManager), INITIALIZE);
//    sceneManager->addScene( new scSelectGame(myPlayerManager), SELECT_GAME);
//    sceneManager->addScene( new scGame1(myPlayerManager), GAME1);
//    sceneManager->addScene( new scGame2(myPlayerManager), GAME2);
//    sceneManager->addScene( new scGame3(myPlayerManager), GAME3);
//    sceneManager->addScene( new scGame3BIS(myPlayerManager), GAME3_BIS);
//    sceneManager->addScene( new scHint(myPlayerManager), HINT);
//    sceneManager->addScene( new scVictory(myPlayerManager), VICTORY);
    
    sceneManager->setDrawDebug(false);
	sceneManager->setCurtainDropTime(1.0);
	sceneManager->setCurtainStayTime(0.0);
	sceneManager->setCurtainRiseTime(1.0);
	sceneManager->setOverlapUpdate(true);
    
    ///////////////////////////////////////
    background.load("Decor_MurEtSol.png");
    
    
}

void ofApp::update(){
	
    //app timebase, to send to all animatable objects
    float dt = 1.0f / (float)ofGetFrameRate();
    
	bigPlayerManager().update();
    sceneManager->update( dt );
    
}


void ofApp::draw(){
    
    // A background to rule them all
    ofSetColor(255);
    ofPushView();
    ofDisableNormalizedTexCoords();
    background.draw(0,0);
    ofEnableNormalizedTexCoords();
    ofPopView();
    
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
        if (key == OF_KEY_RIGHT)
            goToNextScene();
        
        if (key == OF_KEY_LEFT)
            goToPrevScene();
    }
    
    sceneManager->keyPressed(key);
    bigPlayerManager().keyPressed(key);
    
}


void ofApp::windowResized(int w, int h){
	sceneManager->windowResized(w,h); // in case your screens need to know, will forward to all of them
}

// There we'll manage which scene will go next when the previous ends
void ofApp::nextSceneAuto(){
    ofLogNotice() << "Next Scene !!!!! Auto-Launch";
    
    switch (sceneManager->getCurrentSceneID()) {
        case INTRO:
        case INITIALIZE:
        case SELECT_GAME:
        case GAME1:
        case GAME2:
        case GAME3:
        case HINT:
        case VICTORY:
        default:
            goToNextScene();
            break;
    }
}

//// There we'll manage which scene will go next when the previous ends
//void ofApp::someoneSpoke(player & _player){
//    ofLogNotice() << "[ofApp] Someone spoke ! What do yu wanna do ?";
//    
//    switch (sceneManager->getCurrentSceneID()) {
//        case INTRO:
//            goToNextScene();
//            break;
//        case INITIALIZE:
//            break;
//        case SELECT_GAME:
//            ofLogNotice() << "Last spoken word is : " << _player.getLastMessage();
//            // Choix du jeu 1
//            if(ofStringTimesInString(_player.getLastMessage(), "motus") > 0){
//                sceneManager->goToScene(GAME1);
//            }
//            // Choix du jeu 2
//            if(ofStringTimesInString(_player.getLastMessage(), "labyrinthe") > 0){
//                sceneManager->goToScene(GAME2);
//            }
//            // Choix du jeu 3
//            if(ofStringTimesInString(_player.getLastMessage(), "Google") > 0){
//                sceneManager->goToScene(GAME3);
//            }
//            break;
//        case GAME1:
//        case GAME2:
//        case GAME3:
//        case HINT:
//        case VICTORY:
//        default:
//            break;
//    }
//}

void ofApp::goToNextScene(){
    int scId = sceneManager->getCurrentSceneID();
    if(scId == sceneManager->getNumScenes()){
        scId = 1;
    }else{
        scId++;
    }
    sceneManager->goToScene(scId);
}


void ofApp::goToPrevScene(){
    int scId = sceneManager->getCurrentSceneID();
    if(scId == 1){
        scId = sceneManager->getNumScenes();
    }else{
        scId--;
    }
    sceneManager->goToScene(scId);
}
