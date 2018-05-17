//
//  scGame3.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame3.h"

//--------------------------------------------------------------
void scGame3::setup(){
    
    scScene::setup();
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

    //physics
    setupPhysics();
    
    //light
    setupLight();
    
    // Player manager events
    ofAddListener(bigPlayerManager().someoneSpoke,this,&scGame3::someoneSpoke);
    
    //now comes from enigma Singleton
    wantedWord = "BONHEUR";
    
    //view from top
    camera.rotate(-80, ofVec3f(1,0,0));
    
    //load background
//    background.load("Decor_SS-Sol.png");

};


//--------------------------------------------------------------
void scGame3::update(float dt){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    camera.setPosition(ofVec3f(camPosX, camPosY, camPosZ));
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
        randomForce = ofVec3f(forceAmount->x, ofRandom(-forceAmount->y, forceAmount->y), ofRandom(-forceAmount->z, forceAmount->z)) * amountPlayer1;
        applyForceOnCubes(randomForce, ofPoint(-500, 0, 0));
        
        
        float amountPlayer2 = ofMap(bigPlayerManager().getUserVolume(2), volumeBorneMin, volumeBorneMax, volumeBorneMin, volumeBorneMax);
        randomForce = ofVec3f(ofRandom(-forceAmount->x, forceAmount->x), ofRandom(-forceAmount->y, forceAmount->y), -forceAmount->z) * amountPlayer2 * forceMicro2_multiplier;
        applyForceOnCubes(randomForce, ofPoint(-500, 0, 0));
        
        float amountPlayer3 = ofMap(bigPlayerManager().getUserVolume(3), volumeBorneMin, volumeBorneMax, volumeBorneMin, volumeBorneMax);
        randomForce = ofVec3f(-forceAmount->x, ofRandom(-forceAmount->y, forceAmount->y), ofRandom(-forceAmount->z, forceAmount->z)) * amountPlayer3;
        applyForceOnCubes(randomForce, ofPoint(-500, 0, 0));

    }
    

};

//--------------------------------------------------------------
void scGame3::draw(){
    
    
    //draw du background
    ofSetColor(255);
//    ofPushMatrix();
//        ofTranslate(0,0,-200);
//        ofEnableNormalizedTexCoords();
//        background.bind();
//        ofDrawBox(ofGetWidth()/2, ofGetHeight()/2, 0, ofGetWidth()*1.3, ofGetHeight()*1.3, 1);
//        background.unbind();
//    ofPopMatrix();
    
    
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    
    ofSetBackgroundColor(255);
    
    ofEnableLighting();
    spotLight.enable();

    material.setAmbientColor(materialColor);
    material.setDiffuseColor(materialColor);
    
    camera.begin();
    
    if(drawDebug)
    {
        ofSetColor(100, 100, 100);
        ofNoFill();
        ground.draw();
        rightFace.draw();
        leftFace.draw();
        bottom.draw();
        ofFill();
        
        spotLight.draw();
    }
    
    material.begin();
    for(int i=0; i<myCubes.size(); i++)
    {
        myCubes[i]->customDraw();
    }
    material.end();
    ofDisableLighting();
    
    if(drawDebug)
        world.drawDebug();
    
    
    camera.end();
    
    
    ofDisableDepthTest();
    
    if(drawGui)
        gui.draw();
    
    ofDrawBitmapString("volume amount : " + ofToString(amount) + "NumberOfPlayers" + ofToString(bigPlayerManager().getNumberOfPlayers()), 100, 100);
    
    // Draw title
    scScene::drawTitle("Game 3 : Boggle");
    // Draw players
    bigPlayerManager().draw();
    
};

//--------------------------------------------------------------
void scGame3::exit()
{
    gui.saveToFile("gui.xml");
}


//--------------------------------------------------------------
void scGame3::someoneSpoke(player & _player){
    scScene::someoneSpoke(_player);

    std::size_t index = utils::toUpperCase(_player.getLastMessage()).find(utils::toUpperCase(wantedWord));
    if(index != std::string::npos)
    {
        cout << "c'est gagné !!! " << endl;
        winnerColor = _player.getColor();
        ofxSceneManager::instance()->goToScene(7, true, false);
    }    
}

//--------------------------------------------------------------
void scGame3::sceneWillAppear( ofxScene * fromScreen ){
    
    scScene::sceneWillAppear(fromScreen);    
    
    // Erase all words of every one
    bigPlayerManager().freshRestart();

    
    //now comes from enigma Singleton
    bigEnigmaManager().pickNewEnigma(MOTUS);
    wantedWord = utils::toUpperCase(bigEnigmaManager().getCurrentEnigma()->getSolution());
    cout << "setting wantedWord to : " << wantedWord << endl;
    
    
    //clean potentially previous session
    for(int i=0; i<myCubes.size(); i++)
    {
        myCubes[i]->remove();
    }
    myCubes.clear();
    
    
    for(int i=0; i<wantedWord.size(); i++)
    {
        box = new specialBox();
        box->setup(texture, ofToString(wantedWord[i]), 40);
        box->create(world.world, ofVec3f(0, 600, 0), .5, 80, 80, 80);
 
        box->add();
        box->applyForce(START_FORCE_FACTOR*ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)), box->getPosition());
        
        myCubes.push_back(box);
    }
    
    timer = ofGetElapsedTimef();
};

//--------------------------------------------------------------
void scGame3::sceneWillDisappear( ofxScene * toScreen ){
    
};



//--------------------------------------------------------------
void scGame3::keyPressed(int key){

    if(key==' ')
    {
        drawGui = !drawGui;
    }
    
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
    gui.setup();
    gui.add(camPosX.set("camPosX", 0, -1000, 1000));
    gui.add(camPosY.set("camPosY", 800, -1000, 1000));
    gui.add(camPosZ.set("camPosZ", 155, -1000, 2000));
    gui.add(gravity.set("gravity", -250, -500, 250));
    
    gui.add(volumeBorneMin.set("volumeBorneMin", 0, 0.0, 1.0));
    gui.add(volumeBorneMax.set("volumeBorneMax", 0.29, 0.0, 1.0));
    
    gui.add(forceAmount.set("forceAmount", ofVec3f(100,200,100), ofVec3f(0,0,0), ofVec3f(300,300,300)));
    
    gui.add(forceMicro2_multiplier.set("forceMicro2_multiplier", 0.6, 0.1, 1.0));
    
    gui.add(angularDamping.set("angularDamping", 0.815, 0.0, 1.0));
    gui.add(damping.set("damping", 0.25, 0.0, 1.0));
    gui.add(friction.set("friction", 0.75, 0.0, 1.0));
    
    //gui.add(zLight.set("zLight", 0, -1000, 1000));
    gui.add(drawDebug.set("drawDebug", 0));
    gui.loadFromFile("gui.xml");
    drawGui = false;
};


//--------------------------------------------------------------
void scGame3::setupPhysics()
{
    world.setup();
    world.enableDebugDraw();
    world.setCamera(&camera);
    world.setGravity(ofVec3f(0,50,0));
    
    float boxSize = 1000.0;
    float yOffset = 150.0; //so the bottom of the simulation is above the avatars
    
    ground.create( world.world,     ofVec3f(0, 0, 0- yOffset    ),      0., boxSize, 1.f, boxSize );
    ground.setProperties(.25, .55);
    ground.add();
    
    rightFace.create( world.world,  ofVec3f(boxSize/2 - 100, 0, 0- yOffset),    0., 1, boxSize, boxSize );
    rightFace.setProperties(.25, .95);
    rightFace.add();
    
    leftFace.create( world.world,  ofVec3f(-(boxSize/2 - 100), 0, 0- yOffset),    0., 1, boxSize, boxSize );
    leftFace.setProperties(.25, .95);
    leftFace.add();
    
    bottom.create( world.world,  ofVec3f(0, 0, -boxSize/2- yOffset),      0., boxSize, boxSize, 1 );
    bottom.setProperties(.25, .95);
    bottom.add();
    
    front.create(world.world,  ofVec3f(0, 0, boxSize/2 - yOffset - 150),      0., boxSize, boxSize, 1 );
    front.setProperties(.25, .95);
    front.add();
    
    top.create(world.world,  ofVec3f(0, boxSize/2, 0- yOffset),      0., boxSize, 1, boxSize );
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
    spotLight.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    spotLight.setPosition(ofGetWidth()-300, 100, 0);
    material.setShininess( 128);
    lightColor.setBrightness( 255.0f);
    lightColor.setSaturation( 0.f );
    materialColor.setBrightness(255);
    materialColor.setSaturation(0);
    
    materialColor.setHue(0);
};



