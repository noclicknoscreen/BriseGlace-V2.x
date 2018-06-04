//
//  cubeManager.cpp
//  cubes
//
//  Created by Blindsp0t on 03/05/2018.
//
//

#include "cubeManagerMemory.h"


void cubeManagerMemory::setup(int _cubesPositionY, int _espacementCubes)
{
    
    cubeManager::setup(_cubesPositionY, _espacementCubes);
    
    ofEnableDepthTest();

    ofSetBoxResolution(50);
    ofSetSmoothLighting(true);
    ofSetSphereResolution(32);
 
    //lumiere
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

    //font
    font.load(globalFontName, globalFontSizeBig);
    
    //texture
    texture.load("contreplaque.png");
    
    cubeSize = 150;
    
    //load background
    background.load("Decor_MurEtSol.png");
    
    setGrid(4,4);

};

void cubeManagerMemory::setGrid(int _nbLines, int _nbRows){
    
    // Flush all cubes
    myCubes.clear();
    
    for(int idxRow=0; idxRow<_nbRows; idxRow++)
    {
        
        for(int idxLine=0; idxLine<_nbLines; idxLine++)
        {
            cube* tmpCube = new cube();
            
            int step = cubeSize + 2*mEspacementCubes;
            
            ofPoint position((ofGetWidth() - _nbRows*step) / 2, (mCubesPositionY - _nbLines*step) / 2);
            position.x += idxRow*step;
            position.y += idxLine*step;
            position.z = -300;
            
            tmpCube->setup(position, cubeSize);
            tmpCube->setLetter(utils::getRndLetter());
            tmpCube->rotateToLetter();
            
            myCubes.push_back(*tmpCube);
        }
    }
    
}

void cubeManagerMemory::update(ofPoint _lightPos, int cubesRotationSpeed)
{
    spotLight.setPosition(_lightPos.x, _lightPos.y, _lightPos.z);

    for(int i=0; i<myCubes.size(); i++)
    {
        myCubes[i].update(cubesRotationSpeed);
    }

    spotLight.setOrientation( ofVec3f( 0, 45, 30) );
    lightColor.setHue(0);
    spotLight.setDiffuseColor(lightColor);
    material.setSpecularColor(materialColor);
    
};


//--------------------------------------------------------------
void cubeManagerMemory::draw(){

    ofEnableDepthTest();
    
    //draw du background
    ofSetColor(255);
    ofPushMatrix();
        ofTranslate(0,0,-200);
        background.bind();
        ofDrawBox(ofGetWidth()/2, ofGetHeight()/2, 0, ofGetWidth()*1.3, ofGetHeight()*1.3, 1);
        background.unbind();
    ofPopMatrix();
    

    ofEnableLighting();
    spotLight.enable();
    
    for(int i=0; i<myCubes.size(); i++)
    {
        ofPushMatrix();
        
        
            ofTranslate(myCubes[i].position.x, myCubes[i].position.y, myCubes[i].position.z);
            ofRotate(myCubes[i].currentRot, 1.0, 0.0, 0.0);
        
            materialColor.setHue(0);
            material.setAmbientColor(materialColor);
            material.setDiffuseColor(materialColor);
            //material.setSpecularColor(materialColor);

            material.begin();
            ofEnableNormalizedTexCoords();
            texture.bind();
               ofDrawBox(myCubes[i].size, myCubes[i].size ,myCubes[i].size);
            material.end();
            texture.unbind();
            
            
            //FACE BLANCHE
            material.setAmbientColor(myCubes[i].materialColor);
        
            material.setDiffuseColor(ofColor(myCubes[i].materialColor, 140)); //add some transparency here, to keep the texture visible ;)
            material.begin();
        
            ofEnableNormalizedTexCoords();
            //texture.bind();
            for(int i=0; i<myCubes.size(); i++)
            {
                ofPushMatrix();
                ofRotate(180,1,0,0);
                ofDrawRectangle(-myCubes[i].size/2, -myCubes[i].size/2, (myCubes[i].size/2)+0.2, myCubes[i].size, myCubes[i].size);
                ofPopMatrix();
            }
            //texture.unbind();
        
            
            material.end();
            //END FACE BLANCHE
            
            float textHeight, textWidth;
            textWidth = font.getStringBoundingBox("A", 0, 0).getWidth();
            textHeight = font.getStringBoundingBox("A", 0, 0).getHeight();
            
            ofSetColor(0);
            
            ofPushMatrix();
            
                ofTranslate(-textWidth/2, -textHeight/2, -myCubes[i].size/2-1);
                ofRotate(180,0,1,0);
                ofRotate(180,0,0,1);
                font.drawString(myCubes[i].myLetter, 0, 0);
        
            ofPopMatrix();
        
        ofPopMatrix();

        //FIN LETTRE
    }
    spotLight.disable();
    ofDisableLighting();
    
    // DEBUG DRAW
#if defined DRAW_DEBUG
    spotLight.draw();
#endif
    
    ofSetColor(255);
}

void cubeManagerMemory::rotateToWhite(int i)
{
    myCubes[i].rotateToWhite();
}

void cubeManagerMemory::rotateToWood(int i)
{
    myCubes[i].rotateToWood();
}

void cubeManagerMemory::rotateToLetter(int i)
{
    myCubes[i].rotateToLetter();
}







