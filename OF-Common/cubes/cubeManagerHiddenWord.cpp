//
//  cubeManager.cpp
//  cubes
//
//  Created by Blindsp0t on 03/05/2018.
//
//

#include "cubeManagerHiddenWord.h"


void cubeManagerHiddenWord::setup(ofPoint _cubesPos, int _espacementCubes)
{
    // Root Setup -----
    cubeManager::setup(_cubesPos, _espacementCubes);
};

//--------------------------------------------------------------
void cubeManagerHiddenWord::draw(){

    ofEnableDepthTest();
    
//    //draw du background
//    ofSetColor(255);
//    ofPushMatrix();
//        ofTranslate(0,0,-200);
//        background.bind();
//        ofDrawBox(ofGetWidth()/2, ofGetHeight()/2, 0, ofGetWidth()*1.3, ofGetHeight()*1.3, 1);
//        background.unbind();
//    ofPopMatrix();
    

    ofEnableLighting();
    ofSetSmoothLighting(true);
//    spotLightCubes.enable();
    
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
            textureBois.bind();
               ofDrawBox(myCubes[i].size, myCubes[i].size ,myCubes[i].size);
            material.end();
            textureBois.unbind();
            
            
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
    
    // DEBUG DRAW
#if defined DRAW_DEBUG
    spotLight.draw();
#endif
    
//    spotLightCubes.disable();
    ofDisableLighting();
    

    
    ofSetColor(255);
}

void cubeManagerHiddenWord::getWord(string word)
{
    ofLogNotice() << "new word : " << word;
    
    //compute offset between letters
    float wordWidth = (word.size()*cubeSize) + ((word.size()+1) * mEspacementCubes);
    
    myCubes.clear();
    
    for(int i=0; i<word.size(); i++)
    {
        cube* tmpCube = new cube();
        tmpCube->setup(ofPoint(mCubesPosition.x - wordWidth/2 + i*(mEspacementCubes + cubeSize) + cubeSize/2 + mEspacementCubes, mCubesPosition.y, -300), cubeSize);
        tmpCube->setLetter(utils::toUpperCase(ofToString(word[i])));
        myCubes.push_back(*tmpCube);
    }
}





