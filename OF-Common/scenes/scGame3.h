//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "scScene.h"

#include "MSAPhysics3D.h"
#include "particule.h"


using namespace msa::physics;

#define UNITS(s)                (s * ofGetWidth() / 1280.0) // scale to uniform units
#define FORCE_AMOUNT			UNITS(10)
#define	SPRING_MIN_STRENGTH		0.005
#define SPRING_MAX_STRENGTH		0.1
#define	GRAVITY					1
#define SECTOR_COUNT			1		// currently there is a bug at sector borders, so setting this to 1
#define	SPRING_MIN_WIDTH		UNITS(1)
#define SPRING_MAX_WIDTH		UNITS(3)


#define depthDivide 2


class scGame3 : public scScene{

public:
    scGame3(ofEvent<void> _endSceneEvent, playerManager &_manager) : scScene(_endSceneEvent, _manager){
    };
    void setup();
    void update(float dt);
	void draw();
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
    
    ////////////////////////////////////////////
    void initScene();
    void setupLighting();
    void addRandomForce(float f);
    void drawRoom();
    void drawSprings();
    void applyRandomForces();
    void createTestParticules();
    void createParticules(string _word);
    
    void keyPressed(int key);
    
    
    //utils
    float				rotX, rotY		= 0;
    int             	width;
    int         		height;
    float               forceTimer;
    
    //physics
    World3D_ptr         world;
    Attraction3D_ptr    attract;
    
    //the big list
    vector<particule*>   myParticules;
    
    //mouse (view rotation)
    ofPoint mouseClickPos;


};

