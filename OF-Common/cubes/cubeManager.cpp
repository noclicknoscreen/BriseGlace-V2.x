//
//  cubeManager.cpp
//  theBigGame
//
//  Created by Sébastien Albert on 04/06/2018.
//
//

#include "cubeManager.h"


void cubeManager::setup(ofPoint _cubesPos, int _espacementCubes, int _cubeSize)
{
    
    mCubesPosition = _cubesPos;
    mEspacementCubes = _espacementCubes;
    
    ofSetBoxResolution(50);
    ofSetSphereResolution(32);
    
    //lumiere
    spotLightCubes.enable();
    spotLightCubes.setSpotlight();
    spotLightCubes.setSpotlightCutOff(200);
    spotLightCubes.setAttenuation(0.3,0,0); //puissance de la light = inverse de l'attenuation
    spotLightCubes.setSpotConcentration(0.15);
    spotLightCubes.setDiffuseColor( ofColor(50));
    spotLightCubes.setSpecularColor( ofColor(0));
    spotLightCubes.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    material.setShininess(40);
    
    materialColor.setBrightness(255);
    materialColor.setSaturation(0);
    
    //font
    font.load(globalFontName, globalFontSizeBig);
    
    //texture
    textureBois.load("contreplaque.png");
    
    cubeSize = _cubeSize;
}

void cubeManager::update(ofPoint _lightPos, ofPoint _lightAngle, float _cutOff, float _concentration, int cubesRotationSpeed)
{
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
    lightColor.setBrightness( 100.0f);
    lightColor.setSaturation( 0.f );

    spotLightCubes.setDiffuseColor(lightColor);
    
    material.setSpecularColor(ofColor(0));
    
}

void cubeManager::drawTexturedCube(ofImage *texture, int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max)
{
    float realTexCoordX_min = texCoordX_min * texture->getWidth();
    float realTexCoordX_max = texCoordX_max * texture->getWidth();
    float realTexCoordY_min = texCoordY_min * texture->getHeight();
    float realTexCoordY_max = texCoordY_max * texture->getHeight();


    ofPushMatrix();
//    ofTranslate(myCubes[i].position.x, myCubes[i].position.y);
//    ofRotate(myCubes[i].currentRot, 1, 0, 0);
//    ofDrawBox(0, 0, 0, myCubes[i].size, myCubes[i].size, myCubes[i].size);

    texture->bind();

    ofPushMatrix();

    ofTranslate(-myCubes[i].size/2, -myCubes[i].size/2, myCubes[i].size * (0.5+0.002));
    GLfloat tx0 = realTexCoordX_min;
    GLfloat ty0 = realTexCoordY_min;
    GLfloat tx1 = realTexCoordX_max;
    GLfloat ty1 = realTexCoordY_max;

    GLfloat px0 = 0.0f;
    GLfloat py0 = 0.0f;
    GLfloat px1 = myCubes[i].size;
    GLfloat py1 = myCubes[i].size;

    GLfloat tex_coords[] = {
        tx0,ty0,
        tx1,ty0,
        tx1,ty1,
        tx0,ty1
    };
    GLfloat verts[] = {
        px0,py0,
        px1,py0,
        px1,py1,
        px0,py1
    };

    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glTexCoordPointer(2, GL_FLOAT, 0, tex_coords );
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, verts );
    glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );


    ofPopMatrix();

    ofSetColor(255);
    texture->unbind();
    ofPopMatrix();

}

// Here we colorize cubes
void cubeManager::colorizeCube(int cubeId, ofColor _color)
{
    
    int compareNb;
    
    switch (bigEnigmaManager().getCurrentGameType()) {
            
        case IMAGE_GRID:
            // In Memory, we test if the letter is in the solution word
            compareNb = ofStringTimesInString(utils::toUpperCase(bigEnigmaManager().getCurrentEnigma()->getSolution()), myCubes[cubeId].myLetter);
            ofLogNotice() << "Colorize : The letter is [" << myCubes[cubeId].myLetter << "] and the enigma is [" << bigEnigmaManager().getCurrentEnigma()->getSolution() << "]" << " NB=" << compareNb;
            
            if(compareNb > 0){
                // Good, we color
                myCubes[cubeId].setMaterialColor(_color);
            }else{
                // Not Good, keep white
                myCubes[cubeId].setMaterialColor(ofColor::white);
            }
            break;
            
        default:
            // Set the color anyway
            myCubes[cubeId].setMaterialColor(_color);
            break;
    }
    
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
