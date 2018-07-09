//
//  cubeManager.cpp
//  cubes
//
//  Created by Blindsp0t on 03/05/2018.
//
//

#include "cubeManagerHiddenWord.h"


void cubeManagerHiddenWord::setup(ofPoint _cubesPos, int _espacementCubes, int _cubeSize)
{
    // Root Setup -----
    cubeManager::setup(_cubesPos, _espacementCubes, _cubeSize);
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
    
    for(int idxCube=0; idxCube<myCubes.size(); idxCube++)
    {
        ofPushMatrix();
        
        
            ofTranslate(myCubes[idxCube].position.x, myCubes[idxCube].position.y, myCubes[idxCube].position.z);
            ofRotate(myCubes[idxCube].currentRot, 1.0, 0.0, 0.0);
        
            materialColor.setHue(0);
            material.setAmbientColor(materialColor);
            material.setDiffuseColor(materialColor);
            //material.setSpecularColor(materialColor);

            material.begin();
            ofEnableNormalizedTexCoords();
            textureBois.bind();
               ofDrawBox(myCubes[idxCube].size, myCubes[idxCube].size ,myCubes[idxCube].size);
            material.end();
            textureBois.unbind();
            
            
            //FACE BLANCHE
            material.setAmbientColor(myCubes[idxCube].getMaterialColor());
        
            material.setDiffuseColor(ofColor(myCubes[idxCube].getMaterialColor(), 140)); //add some transparency here, to keep the texture visible ;)
            material.begin();
        
            ofEnableNormalizedTexCoords();
            //texture.bind();
            for(int i=0; i<myCubes.size(); i++)
            {
                ofPushMatrix();
                ofRotate(180,1,0,0);
                ofDrawRectangle(-myCubes[idxCube].size/2, -myCubes[idxCube].size/2, (myCubes[idxCube].size/2)+0.2, myCubes[idxCube].size, myCubes[idxCube].size);
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
            
                ofTranslate(-textWidth/2, -textHeight/2, -myCubes[idxCube].size/2-1);
                ofRotate(180,0,1,0);
                ofRotate(180,0,0,1);
        
        font.drawString(utils::toUpperCase(utils::toByteString(myCubes[idxCube].getLetter())), 0, 0);
        
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

void cubeManagerHiddenWord::getWord(wstring word)
{
    ofLogNotice() << "new word : " << utils::toByteString(word);
    
    //compute offset between letters
    float spaceFactor = 0.3f;
    
    int   nbSpace = ofStringTimesInString(utils::toByteString(word), " ");
    // Space is less wide than other letters
    // + 1 espacement cube
    float wordWidth = (word.size() - nbSpace + nbSpace*spaceFactor) * (cubeSize + mEspacementCubes) + mEspacementCubes;
    
    myCubes.clear();
    
    ofPoint posCube(mCubesPosition.x - wordWidth/2 + cubeSize/2 + mEspacementCubes, mCubesPosition.y, mCubesPosition.z);
    
    for(int i=0; i<word.size(); i++)
    {
        
        
        if(word.substr(i,1) != L" "){
            cube* tmpCube = new cube();
            tmpCube->setup(posCube, cubeSize);
            tmpCube->setLetter(word.substr(i, 1));
            myCubes.push_back(*tmpCube);
            
            // Increment position
            posCube.x += mEspacementCubes + cubeSize;
            
        }else{
            // Space, increment position but little
            posCube.x += spaceFactor * (mEspacementCubes + cubeSize);
            
        }
    }
}





