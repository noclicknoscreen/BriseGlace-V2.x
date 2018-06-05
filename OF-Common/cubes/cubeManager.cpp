//
//  cubeManager.cpp
//  theBigGame
//
//  Created by Sébastien Albert on 04/06/2018.
//
//

#include "cubeManager.h"


void cubeManager::setup(int _cubesPositionY, int _espacementCubes)
{
    
    mCubesPositionY = _cubesPositionY;
    mEspacementCubes = _espacementCubes;
    
    ofEnableDepthTest();
    
    ofSetBoxResolution(50);
    ofSetSmoothLighting(true);
    ofSetSphereResolution(32);
    
    //lumiere
    spotLightCubes.enable();
    spotLightCubes.setSpotlight();
    spotLightCubes.setSpotlightCutOff(200);
    spotLightCubes.setAttenuation(0.3,0,0); //puissance de la light = inverse de l'attenuation
    spotLightCubes.setSpotConcentration(0.15);
    spotLightCubes.setDiffuseColor( ofColor(255.f, 255.f, 255.f));
    spotLightCubes.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    spotLightCubes.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    material.setShininess( 128);
    lightColor.setBrightness( 255.0f);
    lightColor.setSaturation( 0.f );
    materialColor.setBrightness(255);
    materialColor.setSaturation(0);
    
    //font
    font.load(globalFontName, globalFontSizeBig);
    
    //texture
    textureBois.load("contreplaque.png");
    
    cubeSize = 150;
}

void cubeManager::update(ofPoint _lightPos, ofPoint _lightAngle, float _cutOff, float _concentration, int cubesRotationSpeed)
{
    ofSetSmoothLighting(true);
    spotLightCubes.setPosition(_lightPos.x, _lightPos.y, _lightPos.z);
    spotLightCubes.setOrientation(ofVec3f(_lightAngle.x, _lightAngle.y, _lightAngle.z));
    spotLightCubes.setSpotlightCutOff(_cutOff);
    spotLightCubes.setSpotConcentration(_concentration);
    
//    ofLog() << "Light Position : " << spotLight.getPosition() << "Light GLOBLAL Position : " << spotLight.getGlobalPosition();
//    ofLog() << "Light Orientation : " << spotLight.getOrientationEuler() << "Light GLOBAL Orientation : " << spotLight.getGlobalOrientation();
    
    for(int i=0; i<myCubes.size(); i++)
    {
        myCubes[i].update(cubesRotationSpeed);
    }
    
    lightColor.setHue(0);
    spotLightCubes.setDiffuseColor(lightColor);
    material.setSpecularColor(materialColor);
    
}


void cubeManager::colorizeCube(int cubeId, ofColor _color)
{
    myCubes[cubeId].setMaterialColor(_color);
}
void cubeManager::rotateToWhite(int _idxCube)
{
    myCubes[_idxCube].rotateToWhite();
}

void cubeManager::rotateToWood(int _idxCube)
{
    myCubes[_idxCube].rotateToWood();
}

void cubeManager::rotateToLetter(int _idxCube)
{
    myCubes[_idxCube].rotateToLetter();
}
void cubeManager::rotateAllToWhite()
{
    for(int idxCube = 0; idxCube < myCubes.size(); idxCube++){
        myCubes[idxCube].rotateToWhite();
    }
}

void cubeManager::rotateAllToWood()
{
    for(int idxCube = 0; idxCube < myCubes.size(); idxCube++){
        myCubes[idxCube].rotateToWood();
    }
}

void cubeManager::rotateAllToLetter()
{
    for(int idxCube = 0; idxCube < myCubes.size(); idxCube++){
        myCubes[idxCube].rotateToLetter();
    }
}
