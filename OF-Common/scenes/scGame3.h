//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofxGui.h"
#include "ofxBullet.h"

#include "scGame.h"
#include "cubeRigidBody.h"

#define START_FORCE_FACTOR 300//250//100
#define PLAY_FORCE_FACTOR  7

class scGame3 : public scGame{

public:

    
    void setup();
    void update(float dt);
	void draw();
    void setupGui();
    void setupPhysics(ofVec3f _boxSize);
    void setupLight();
    
    void someoneSpoke(player & _player);
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    void timerEnd();
    void timerSignWinEnd();
    
    void keyPressed(int key);
    void exit();
    
    //physics
    ofxBulletWorldRigid			world;
    ofxBulletBox				ground, rightFace, leftFace, bottom, front, top;
    cubeRigidBody*                 box;
    
    void applyForceOnCubes(ofVec3f force, ofPoint _frcPos);
    float amount;
    
    //camera
    //ofEasyCam					camera;
    ofCamera					camera;
    
    //the word to find
    string wantedWord;
    
    //texture
    ofImage texture;

    //the cubes
    vector<cubeRigidBody*>          myCubes;
    
    //background image
//    ofImage background;
    
    //parameters
    bool                         bDrawGui;
    
    ofxPanel                     gui;
    ofParameterGroup             group;
    
    ofParameter<float>           camPosX, camPosY, camPosZ, gravity, angularDamping, damping, friction;
    ofParameter<float>           volumeBorneMin, volumeBorneMax;
    ofParameter<float>           forceMicro2_multiplier;
    ofParameter<float>           bonusY;
    ofParameter<float>           constantZ;
    ofParameter<ofVec3f>         forceAmount;
    ofParameter<float>           zLight;
    
    ofParameter<bool>           testIs1;
    ofParameter<bool>           testIs2;
    ofParameter<bool>           testIs3;
    
    //lumiere
    ofLight spotLight;
    ofColor lightColor;
    ofColor materialColor;
    ofMaterial material;
    
    //timer
    float timer;
    
    //winner color (for game3BIS ;)
protected:
    bool colorizeCubes;
    
    // TIMERS
//private:
//    timer mTimerEndScene;
//    void  timerEndScene();
    
};

