//
//  scGame3.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame3.h"

//#define DRAW_DEBUG

//=======================================================================
//
//======= MOT BRASSE ====================================================
//
//=======================================================================

//--------------------------------------------------------------
void scGame3::setup(){
    
    scGame::setup();
    
    ofLogNotice() << "Game 3 : Setup !";
    
    //gui
    setupGui();
    
    //OF
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAntiAliasing();
    ofSetBoxResolution(30);
    
    //texture
    texture.load("contreplaque.png");
    
    //camera
    camera.setPosition(ofVec3f(camPosX, camPosY, camPosZ));
    
    //light
    setupLight();
    
    //now comes from enigma Singleton
    //    wantedWord = "BONHEUR";
    
    //view from top
    camera.rotate(-80, ofVec3f(1,0,0));
    
    //load background
    //    background.load("Decor_SS-Sol.png");
    
    colorizeCubes=false;
    
};


//--------------------------------------------------------------
void scGame3::update(float dt){
    
    scGame::update(dt);
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    camera.setGlobalPosition(ofVec3f(camPosX, camPosY, camPosZ));
    world.setGravity(ofVec3f(0,gravity, 0));
    
    world.update();
    
    for(int i=0; i<myCubes.size(); i++)
    {
        myCubes[i]->setActivationState(1);
        
        myCubes[i]->setDamping(damping);
        myCubes[i]->setAngularDamping(angularDamping);
        myCubes[i]->setFriction(friction);
    }
    
    //light
    spotLight.setOrientation( ofVec3f( 0, 45, 30) );
    spotLight.setPosition(1600, 483,0);
    lightColor.setHue(0);
    spotLight.setDiffuseColor(lightColor);
    material.setSpecularColor(materialColor);
    
    //apply forces after 5 seconds
    if(ofGetElapsedTimef() - timer > 5)
    {
        
        ofVec3f randomForce;
        float amountPlayer1 = ofMap(bigPlayerManager().getUserVolume(1), volumeBorneMin, volumeBorneMax, volumeBorneMin, volumeBorneMax);
        if(testIs1){
            amountPlayer1 = bigPlayerManager().getUserVolume(4);
        }
        randomForce = ofVec3f(
                              forceAmount->x,
                              ofRandom(-forceAmount->y, forceAmount->y) + bonusY,
                              ofRandom(-forceAmount->z, forceAmount->z)
                              )
        * amountPlayer1;
        applyForceOnCubes(randomForce, ofPoint(-500, 0, 0));
        
        float amountPlayer2 = ofMap(bigPlayerManager().getUserVolume(2), volumeBorneMin, volumeBorneMax, volumeBorneMin, volumeBorneMax);
        if(testIs2){
            amountPlayer2 = bigPlayerManager().getUserVolume(4);
        }
        randomForce = ofVec3f(
                              ofRandom(-forceAmount->x, forceAmount->x),
                              ofRandom(forceAmount->y) + bonusY,
                              ofRandom(-forceAmount->z, forceAmount->z)
                              )
        * amountPlayer2 * forceMicro2_multiplier;
        applyForceOnCubes(randomForce, ofPoint(-500, 0, 0));
        
        float amountPlayer3 = ofMap(bigPlayerManager().getUserVolume(3), volumeBorneMin, volumeBorneMax, volumeBorneMin, volumeBorneMax);
        if(testIs3){
            amountPlayer3 = bigPlayerManager().getUserVolume(4);
        }
        randomForce = ofVec3f(
                              -forceAmount->x,
                              ofRandom(-forceAmount->y, forceAmount->y) + bonusY,
                              ofRandom(-forceAmount->z, forceAmount->z)
                              )
        * amountPlayer3;
        applyForceOnCubes(randomForce, ofPoint(-500, 0, 0));
        
        randomForce = ofVec3f(0,
                              0,
                              constantZ
                              );
        applyForceOnCubes(randomForce, ofPoint(-500, 0, 0));
        
    }
    
    
    //    mTimerEndScene.update(dt);
    
};

//--------------------------------------------------------------
void scGame3::draw(){
    
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    
    ofSetBackgroundColor(255);
    
    ofEnableLighting();
    ofSetSmoothLighting(true);
    
    material.setAmbientColor(materialColor);
    material.setDiffuseColor(materialColor);
    
    // Draw mother of draw
    scGame::draw();
    
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
        myCubes[i]->customDraw();
    }
    material.end();
    ofDisableLighting();
    
#if defined DRAW_DEBUG
    world.drawDebug();
#endif
    
    
    camera.end();
    
    ofDisableDepthTest();
    
    if(bDrawGui){
        ofDisableLighting();
        gui.draw();
    }
    
#if defined DRAW_DEBUG
    ofDrawBitmapString("volume amount : " + ofToString(amount) + "NumberOfPlayers" + ofToString(bigPlayerManager().getNumberOfPlayers()), 100, 100);
#endif
    
    
    scScene::drawTitle("Mot brassé");
    scScene::drawSubTitle("Trouve " + ofToString(bigEnigmaManager().getCurrentEnigma()->getTheme()));
    scScene::drawSubTitle("Parlez-moi dans l'oreille pour retourner les cubes", ofColor::black, ofPoint(0, 50));
    
    // Draw players
    //    if(drawWinnerSign)
    //        bigPlayerManager().draw(bigPlayerManager().getWinnerUserId(), "c'est gagné");
    //    else if(drawHintSign)
    //        bigPlayerManager().draw(hintUserId, "veux-tu un indice?");
    //    else
    bigPlayerManager().draw();
    
    
};

//--------------------------------------------------------------
void scGame3::exit()
{
    gui.saveToFile(settingsFileNameGame3);
}

//--------------------------------------------------------------
void scGame3::someoneSpoke(player & _player){
    // We don't do the root (because we want to see the hint anyway)
    scScene::someoneSpoke(_player);
    //
    //    std::size_t index = utils::toUpperCase(_player.getLastMessage()).find(utils::toUpperCase(wantedWord));
    //    if(index != std::string::npos)
    //    {
    //        ofLogNotice() << "c'est gagné !!! ";
    //        bigPlayerManager().setWinnerUserId(_player.getNumber());
    //        restartTimerSignWin();
    //        drawWinnerSign = true;
    //
    //        ofRemoveListener(bigPlayerManager().someoneSpoke,this,&scGame3::someoneSpoke);
    //
    //        //ofxSceneManager::instance()->goToScene(7, true, false);
    //    }
    //
    
    int compare = ofStringTimesInString(utils::toUpperCase(_player.getLastMessage()), utils::toUpperCase(bigEnigmaManager().getCurrentEnigma()->getSolution()));
    if(compare > 0)
    {
        ofLogNotice() << "We have a winner [" << _player.getLastMessage() << "] = [" << bigEnigmaManager().getCurrentEnigma()->getSolution() << "], compare = " << compare;
        bigPlayerManager().setWinnerUserId(_player.getNumber());
        bigPlayerManager().startSign(_player.getNumber(), "C'est gagné !");
        restartTimerSignWin();
        stopHint();
        
        //        drawWinnerSign = true;
        
        ofRemoveListener(bigPlayerManager().someoneSpoke,this,&scGame3::someoneSpoke);
        
    }else{
        ofLogNotice() << "Final comparaison failed [" << _player.getLastMessage() << "] different from [" << bigEnigmaManager().getCurrentEnigma()->getSolution() << "], compare = " << compare;
    }
    
}

// VICTORY Event , go to scene you prefer
void scGame3::timerSignWinEnd(){
    scGame::timerSignWinEnd();
    ofxSceneManager::instance()->goToScene(GAME3_BIS);
}

//--------------------------------------------------------------
void scGame3::sceneWillAppear( ofxScene * fromScreen ){
    
    scGame::sceneWillAppear(fromScreen);
    spotLight.enable();
    
    // Player manager events
    ofAddListener(timerSignWin.timerEnd,    this,&scGame3::timerSignWinEnd);
    
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke,this,&scGame3::someoneSpoke);
    
    //    // Erase all words of every one
    //    bigPlayerManager().freshRestart();
    
    // On ne refiat pas ca si on vient de l'indice
    if(fromScreen->getSceneID() != HINT){
        
        // Reset winner
        bigPlayerManager().setWinnerUserId(0);
        
        //now comes from enigma Singleton
        bigEnigmaManager().pickNewEnigma(BOGGLE);
        
        wantedWord = utils::toWString(bigEnigmaManager().getCurrentEnigma()->getSolution());
        ofLogNotice() << "setting wantedWord to : " << utils::toByteString(wantedWord);
        
        //physics
        setupPhysics(ofVec3f(1000.0, 1000.0, 1000.0));

        // Clean potentially previous session -----------------------------------------------------------
        for(int i=0; i<myCubes.size(); i++)
        {
            myCubes[i]->remove();
        }
        myCubes.clear();
        
        // Create all cubes -----------------------------------------------------------------------------
        for(int i=0; i<wantedWord.size(); i++)
        {
            
            ofVec3f rdnStartPosition;
            rdnStartPosition.x = ofRandom(-100, 100);
            rdnStartPosition.y = ofRandom(550, 600);
            rdnStartPosition.z = ofRandom(-50, 50);
            
            box = new cubeRigidBody();
            box->setup(texture, wantedWord.substr(i,1));
            box->create(world.world, rdnStartPosition, .5, 80, 80, 80);
//            box->create(world.world, ofVec3f(0, 600, 0), .5, 80, 80, 80);
            
            box->add();
            box->applyForce(START_FORCE_FACTOR*ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)), box->getPosition());
            
            myCubes.push_back(box);
            
        }
        
    }
    
    
    timer = ofGetElapsedTimef();
    
    bigPlayerManager().setWinnerUserId(0);
    
    //    mTimerEndScene.startTimer(45);
    
    //    drawHintSign = 0;
    //    drawWinnerSign = 0;
    
};

//--------------------------------------------------------------
void scGame3::sceneWillDisappear( ofxScene * toScreen ){
    
    scGame::sceneWillDisappear(toScreen);
    spotLight.disable();
    
    // Disable timer events
    ofRemoveListener(timerSignWin.timerEnd,     this,&scGame3::timerSignWinEnd);
    
    // Player manager events
    ofRemoveListener(bigPlayerManager().someoneSpoke,this,&scGame3::someoneSpoke);
    
};



//--------------------------------------------------------------
void scGame3::keyPressed(int key){
    
    
    if(key == 's') {
        gui.saveToFile(settingsFileNameGame3);
    }
    if(key == 'l') {
        gui.loadFromFile(settingsFileNameGame3);
    }
    if(key==' ' )
        bDrawGui = !bDrawGui;
    
    if(key == 'f')
    {
        for(int i=0; i<myCubes.size(); i++)
        {
            ofVec3f randomForce = ofVec3f(ofRandom(-forceAmount->x, forceAmount->x), ofRandom(-forceAmount->y, forceAmount->y), ofRandom(-forceAmount->z, forceAmount->z));
            myCubes[i]->applyForce(randomForce, ofVec3f(-500,0,0));
        }
    }
    
    if(key=='c') //VIEW FROM TOP
    {
        camPosX = 0;
        camPosY = 550;
        camPosZ = 0;
        
        camera.rotate(-80, ofVec3f(1,0,0));
    }
};

//--------------------------------------------------------------
void scGame3::applyForceOnCubes(ofVec3f force, ofPoint _frcPos)
{
    for(int i=0; i<myCubes.size(); i++)
    {
        myCubes[i]->applyForce(force, _frcPos);
    }
}

//--------------------------------------------------------------
void scGame3::setupGui()
{
    //gui
    
    group.setName("Game3");
    group.add(camPosX.set("camPosX", 0, -3000, 3000));
    group.add(camPosY.set("camPosY", 800, -3000, 3000));
    group.add(camPosZ.set("camPosZ", 155, -3000, 3000));
    group.add(gravity.set("gravity", -250, -500, 250));
    
    group.add(volumeBorneMin.set("volumeBorneMin", 0, 0.0, 1.0));
    group.add(volumeBorneMax.set("volumeBorneMax", 0.29, 0.0, 1.0));
    
    group.add(forceAmount.set("forceAmount", ofVec3f(100,200,100), ofVec3f(0,0,0), ofVec3f(300,300,300)));
    
    group.add(forceMicro2_multiplier.set("forceMicro2_multiplier", 0.6, 0.1, 1.0));
    group.add(bonusY.set("bonusY", 0, 0, 300));
    group.add(constantZ.set("constantZ", 0, -300, 300));
    
    group.add(angularDamping.set("angularDamping", 0.815, 0.0, 1.0));
    group.add(damping.set("damping", 0.25, 0.0, 1.0));
    group.add(friction.set("friction", 0.75, 0.0, 1.0));
    
    group.add(testIs1.set("testIs1", false));
    group.add(testIs2.set("testIs2", false));
    group.add(testIs3.set("testIs3", false));
    
    //gui.add(zLight.set("zLight", 0, -1000, 1000));
    
    gui.setup(group);
    gui.loadFromFile(settingsFileNameGame3);
    
    bDrawGui = false;
};


//--------------------------------------------------------------
void scGame3::setupPhysics(ofVec3f _boxSize)
{
    world.setup();
    world.enableDebugDraw();
    world.setCamera(&camera);
    world.setGravity(ofVec3f(0,50,0));
    
    float   yBottomOffset = 150.0;    // so the bottom of the simulation is above the avatars
    float   yTopOffset = 500.0;       // and the top is below the text
    
    //    void create(btDiscreteDynamicsWorld* a_world, ofVec3f a_loc, float a_mass, float a_sizeX, float a_sizeY, float a_sizeZ );
    
    ground.create   (world.world, ofVec3f(0, 0, 0 - yBottomOffset), 0., _boxSize.x, 1.f, _boxSize.z);
    ground.setProperties(.25, .55);
    ground.add();
    
    rightFace.create(world.world, ofVec3f(_boxSize.x/2 - 100, 0, 0 - yBottomOffset), 0., 1, _boxSize.y, _boxSize.z * 5);
    rightFace.setProperties(.25, .95);
    rightFace.add();
    
    leftFace.create (world.world, ofVec3f(-(_boxSize.x/2 - 100), 0, 0- yBottomOffset), 0., 1, _boxSize.y, _boxSize.z * 5);
    leftFace.setProperties(.25, .95);
    leftFace.add();
    
    bottom.create   (world.world, ofVec3f(0, 0, -_boxSize.z/2 -yBottomOffset + yTopOffset), 0., _boxSize.x, _boxSize.y, 1 );
    bottom.setProperties(.25, .95);
    bottom.add();
    
    front.create    (world.world, ofVec3f(0, 0, _boxSize.z/2 - yBottomOffset - 150), 0., _boxSize.x, _boxSize.y, 1 );
    front.setProperties(.25, .95);
    front.add();
    
    top.create      (world.world, ofVec3f(0, _boxSize.y/2, 0- yBottomOffset), 0., _boxSize.x, 1, _boxSize.z );
    top.setProperties(.25, .95);
    //top.add();
    
};


//--------------------------------------------------------------
void scGame3::setupLight()
{
    spotLight.setSpotlight();
    spotLight.setSpotlightCutOff(200);
    spotLight.setAttenuation(0.3,0,0); //puissance de la light = inverse de l'attenuation
    spotLight.setSpotConcentration(0.15);
    spotLight.setDiffuseColor( ofColor(255.f, 255.f, 255.f));
    spotLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
//    spotLight.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    spotLight.setPosition(ofGetWidth()-300, 100, 0);
    material.setShininess( 128);
    lightColor.setBrightness( 255.0f);
    lightColor.setSaturation( 0.f );
    materialColor.setBrightness(255);
    materialColor.setSaturation(0);
    
    materialColor.setHue(0);
};



