#include "ofApp.h"

//#define DRAW_DEBUG

void ofApp::setup(){

	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
    ofBackground(ofColor::white);
	ofEnableSmoothing();
    
    bFullScreen = true;
    setFullScreen();
    
    ///////////////////////////////////////
    myFont.load("KGTenThousandReasons.ttf", 28, true, true);
    
	///////////////////////////////////////
    // add the newFloat method to listen for eventsAddon newFloatEvent
    ofAddListener(nextSceneEvent,this,&ofApp::nextSceneAuto);
    
    ///////////////////////////////////////
    bigPlayerManager().setup();
    
    /////////////////////////////////////
    bigEnigmaManager().setup();
    
    ///////////////////////////////////////
	sceneManager = ofxSceneManager::instance();
    
    sceneManager->addScene( new scSelectGame(), SELECT_GAME);
    sceneManager->addScene( new scGame1(), GAME1);
    sceneManager->addScene( new scGame2(), GAME2);
    sceneManager->addScene( new scGame3(), GAME3);
    sceneManager->addScene( new scGame3Bis(), GAME3_BIS);
    sceneManager->addScene( new scHint(), HINT);
    sceneManager->addScene( new scVictory(), VICTORY);
    sceneManager->addScene( new scPartners(), PARTNERS);

    sceneManager->setDrawDebug(false);
	sceneManager->setCurtainDropTime(1.0);
	sceneManager->setCurtainStayTime(0.0);
	sceneManager->setCurtainRiseTime(1.0);
	sceneManager->setOverlapUpdate(true);
    
    ///////////////////////////////////////
    background.load("Decor_MurEtSol-A01.jpg");
    
    ///////////////////////////////////////
#ifdef _DEBUG
    // debug only code
    
#else
    // release only code
    ofFile fileLog("../../../Scripts/appLog.txt");
    if(fileLog.exists()){
        fileLog.remove();
    }
    
    ofSetLogLevel(OF_LOG_WARNING);
    ofLogToFile("../../../Scripts/appLog.txt", true); //set channel to log file. log file resides in the /bin/data folder
#endif
    
    
    
    
}

void ofApp::update(){
	
    //app timebase, to send to all animatable objects
    float dt = 1.0f / (float)ofGetFrameRate();
    
	bigPlayerManager().update();
    sceneManager->update(dt);
    
}


void ofApp::draw(){
    
    
    // A background to rule them all
    ofSetColor(255);
    ofPushView();
    ofDisableNormalizedTexCoords();
    ofDisableLighting();
    background.draw(0,0);
    ofEnableNormalizedTexCoords();
    ofPopView();
    
	sceneManager->draw();
    
//    string oeuvre = "Ïuvre";
//    myFont.drawString(oeuvre, 100, 100);
    
#if defined DRAW_DEBUG
    ofSetColor(255,0,0);
    ofDrawBitmapString( "press 1, 2, or 3 to change scene", ofGetWidth() - 290, ofGetHeight() - 10);
#endif
    
}


//if you require mouseMoved events in your scenes, forward them to the SceneManager. Same for any other events
void ofApp::mousePressed( int x, int y, int button ){
	sceneManager->mousePressed(x, y, button);
}

void ofApp::keyPressed(int key){
	
    if (key == '1') sceneManager->goToScene(SELECT_GAME);
    if (key == '2') sceneManager->goToScene(GAME1);
    if (key == '3') sceneManager->goToScene(GAME2);
    if (key == '4') sceneManager->goToScene(GAME3);
    if (key == '5') sceneManager->goToScene(GAME3_BIS);
    if (key == '6') sceneManager->goToScene(HINT);
    if (key == '7') sceneManager->goToScene(VICTORY);
    if (key == '8') sceneManager->goToScene(PARTNERS);
    
    if (key == OF_KEY_RIGHT || key == OF_KEY_LEFT){
        if (key == OF_KEY_RIGHT)
            goToNextScene();
        
        if (key == OF_KEY_LEFT)
            goToPrevScene();
    }
    
    if(key== 'f')
    {
        bFullScreen = !bFullScreen;
        setFullScreen();
    }

    
    sceneManager->keyPressed(key);
    bigPlayerManager().keyPressed(key);
    
}

void ofApp::setFullScreen(){
//    ofSetFullscreen(bFullScreen);
    if(bFullScreen==true){
        ofHideCursor();
    }else{
        ofShowCursor();
    }
    
}

void ofApp::windowResized(int w, int h){
	sceneManager->windowResized(w,h); // in case your screens need to know, will forward to all of them
}

// There we'll manage which scene will go next when the previous ends
void ofApp::nextSceneAuto(){
    ofLogNotice() << "Next Scene !!!!! Auto-Launch";
    
    switch (sceneManager->getCurrentSceneID()) {
//        case INTRO:
//        case INITIALIZE:
        case SELECT_GAME:
        case GAME1:
        case GAME2:
        case GAME3:
        case HINT:
        case VICTORY:
        case PARTNERS:
        default:
            goToNextScene();
            break;
    }
}

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
