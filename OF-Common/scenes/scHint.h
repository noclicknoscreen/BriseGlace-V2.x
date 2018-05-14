//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "scScene.h"
#include "ofMain.h"
#include "cube.h"
#include "ofxTextSuite.h"


class scHint : public scScene{

public:
    scHint(ofEvent<void> _endSceneEvent, playerManager &_manager) : scScene(_endSceneEvent, _manager){
    };
    void setup();
    void update(float dt);
	void draw();
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
    void drawTexturedCube(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max);
    void drawTexturedCubeTEXT(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max);
    void setRevealMode(){revealMode = true;}
    
    vector<cube> myCubes;

    
private :
    //cubes attributes
    float cubeSize;
    float totalWidth;
    float yPos;
    
    //image to be revealed
    ofImage texture;
    
    //utils
    bool revealMode;
    int cubeIndex;
    
    //font
    ofTrueTypeFont font;
    
    //fbo to draw text, to be used as texture
    ofFbo textFbo;
    ofImage textImageFromFbo;
    
    //lumiere
    ofLight spotLight;
    ofColor lightColor;
    ofColor materialColor;
    ofMaterial material;
    
    //text
    ofxTextBlock myText;
    
    //timer
    float timer;

};

