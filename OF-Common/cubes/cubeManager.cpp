//
//  cubeManager.cpp
//  cubes
//
//  Created by Blindsp0t on 03/05/2018.
//
//

#include "cubeManager.h"


void cubeManager::setup()
{
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
    font.load("Avenir.ttc", 24);
    
    //texture
    texture.load("contreplaque.png");
    //ofDisableNormalizedTexCoords();
    //ofDisableArbTex();
    
    cubeSize = 80;    

};

void cubeManager::update(ofPoint _lightPos, int cubesRotationSpeed)
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
void cubeManager::draw(){

    ofEnableDepthTest();
    
    //fond
    ofSetColor(200);
    ofPushMatrix();
    ofTranslate(0,0,-200);
    ofDrawBox(0, 0, 0, ofGetWidth()*3, ofGetHeight()*3, 1);
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
    spotLight.draw();
    
    ofSetColor(0);
    font.drawString(consigne , ofGetWidth()/2 - consigneWidth/2, consignesPositionY);
    ofSetColor(255);

}

void cubeManager::getWord(string word)
{
    cout << "new word : " << word << endl;
    
    //compute offset between letters
    float wordWidth = (word.size()*cubeSize) + ((word.size()+1) * espacementCubes);
    
    myCubes.clear();
    
    for(int i=0; i<word.size(); i++)
    {
        cube* tmpCube = new cube();
        tmpCube->setup(ofPoint((ofGetWidth()-wordWidth)/2 + i*(espacementCubes + cubeSize) + cubeSize/2 + espacementCubes, cubesPositionY,-300), cubeSize);
        tmpCube->setLetter(ofToString(word[i]));
        myCubes.push_back(*tmpCube);
    }
    
    
    consigne = "Derrière ces " + ofToString(word.size()) + " lettres se cache un mot";
    consigneWidth = font.getStringBoundingBox(consigne, 0, 0).getWidth();
    
    
}



void cubeManager::rotateToWhite(int i)
{
    myCubes[i].rotateToWhite();
}

void cubeManager::rotateToWood(int i)
{
    myCubes[i].rotateToWood();
}

void cubeManager::rotateToLetter(int i)
{
    myCubes[i].rotateToLetter();
}

void cubeManager::colorizeCube(int cubeId, ofColor _color)
{
    myCubes[cubeId].setMaterialColor(_color);
}






