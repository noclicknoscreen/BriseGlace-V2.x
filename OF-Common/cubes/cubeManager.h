//
//  cubeManager.hpp
//  theBigGame
//
//  Created by Sébastien Albert on 04/06/2018.
//
//

#pragma once

#include "cube.h"
#include "enigmaManager.h"
#include "utils.h"

class cubeManager
{
    
    // ------------------
    // METHODS ---------
    protected :
    void setup(int _cubesPositionY, int _espacementCubes);
    
public:
    void update(ofPoint _lightPos, ofPoint _lightAngle, float _cutOff, float concentration, int cubesRotationSpeed);
    
    void colorizeCube(int cubeId, ofColor _color);
    
    //cubes
    void rotateToWhite(int i);
    void rotateToWood(int i);
    void rotateToLetter(int i);
    
    void rotateAllToWhite();
    void rotateAllToWood();
    void rotateAllToLetter();
    
    // ------------------
    // MEMBERS ---------
    protected :
    int mCubesPositionY;
    int mEspacementCubes;
    
    //lumiere
    ofLight spotLightCubes;
    ofColor lightColor;
    ofColor materialColor;
    ofMaterial material;
    
    //police de caracteres
    ofTrueTypeFont              font;
    
    //texture
    ofImage                     textureBois;
    
    //cubes size
    float                       cubeSize;
    
public:
    vector<cube>                myCubes;
    
    
};

