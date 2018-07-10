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
    void setup(ofPoint _cubesPos, int _espacementCubes, int _cubeSize);
    
public:
    void update(ofPoint _lightPos, ofPoint _lightAngle, float _cutOff, float concentration, float _cubesRotationSpeed);
    void drawTexturedCube(ofImage *image, int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max);
    void colorizeCube(int cubeId, ofColor _color);
    void colorizeAllCubes(ofColor _color);
    
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
    ofPoint mCubesPosition;
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
    
    void disableLight(){spotLightCubes.disable();};
    
};

