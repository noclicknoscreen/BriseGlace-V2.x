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
    setGrid(4,4);

};

void cubeManagerMemory::setGrid(int _nbLines, int _nbRows){
    
    // Flush all cubes
    myCubes.clear();
    mContent = "";
    
    // Set the shape (how many lines and rows)
    mNbLines = _nbLines;
    mNbRows = _nbRows;
    
    // load the big image
    answerFullImage = bigEnigmaManager().getCurrentEnigma()->getImage(REWARD);
    answerFullImage.resize(_nbRows*cubeSize, _nbLines*cubeSize);
    
    for(int idxRow=0; idxRow<_nbRows; idxRow++)
    {
        
        for(int idxLine=0; idxLine<_nbLines; idxLine++)
        {
            cube* tmpCube = new cube();
            int step = cubeSize + 2*mEspacementCubes;
            string rndLetter;
            do{
               rndLetter = utils::getRndLetter();
            }while(ofStringTimesInString(mContent, rndLetter) > 0 && mContent != "");
            
            ofPoint position(0.5*(ofGetWidth() - _nbRows*step) + 0.5*step, 0.5*(mCubesPositionY - _nbLines*step) + 0.5*step);
            position.x += idxRow*step;
            position.y += idxLine*step;
            position.z = -300;
            
            tmpCube->setup(position, cubeSize);
            tmpCube->setLetter(rndLetter);
            tmpCube->rotateToLetter();
            
            mContent += rndLetter;
            
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
    ofEnableLighting();
    ofSetSmoothLighting(true);
    spotLight.enable();
    
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
            texture.bind();
               ofDrawBox(myCubes[idxCube].size, myCubes[idxCube].size ,myCubes[idxCube].size);
            material.end();
            texture.unbind();
            
            // FACE AVEC IMAGE --------------------------------------------------
            ofPushMatrix();
            material.begin();
            material.setAmbientColor(myCubes[idxCube].materialColor);
            material.setDiffuseColor(ofColor(myCubes[idxCube].materialColor, 140)); //add some transparency here, to keep the texture visible ;)
        
        
            int row = idxCube % mNbRows;
            int line = idxCube / mNbLines;
        
//            ofLog() << "We draw a cutted image [line, row] = [" << line << "," << row << "]";
        
            ofDisableNormalizedTexCoords();
            drawTexturedCube(idxCube,
                             float(line*answerFullImage.getWidth()/mNbRows),
                             float((line+1)*answerFullImage.getWidth()/mNbRows),
                             float(row*answerFullImage.getHeight()/mNbLines),
                             float((row+1)*answerFullImage.getHeight()/mNbLines)
                             );
        
            material.end();
            ofPopMatrix();
            // END FACE BLANCHE --------------------------------------------------
        
            // FACE BLANCHE --------------------------------------------------
            material.begin();
            material.setAmbientColor(myCubes[idxCube].materialColor);
            material.setDiffuseColor(ofColor(myCubes[idxCube].materialColor, 140)); //add some transparency here, to keep the texture visible ;)
        
            ofEnableNormalizedTexCoords();
            for(int i=0; i<myCubes.size(); i++)
            {
                ofPushMatrix();
                ofRotate(180,1,0,0);
                ofDrawRectangle(-myCubes[i].size/2, -myCubes[i].size/2, (myCubes[i].size/2)+0.2, myCubes[i].size, myCubes[i].size);
                ofPopMatrix();
            }
            material.end();
            // END FACE BLANCHE --------------------------------------------------
        
            // DEBUT LETTRE ------------------------------------------------
            float textHeight, textWidth;
            textWidth = font.getStringBoundingBox("A", 0, 0).getWidth();
            textHeight = font.getStringBoundingBox("A", 0, 0).getHeight();
            
            ofSetColor(0);
            
            ofPushMatrix();
            
                ofTranslate(-textWidth/2, -textHeight/2, -myCubes[idxCube].size/2-1);
                ofRotate(180,0,1,0);
                ofRotate(180,0,0,1);
                font.drawString(myCubes[idxCube].myLetter, 0, 0);
        
            ofPopMatrix();
            // FIN LETTRE --------------------------------------------------
        
        ofPopMatrix();

        
    }
    spotLight.disable();
    ofDisableLighting();
    
    // DEBUG DRAW
#if defined DRAW_DEBUG
    spotLight.draw();
#endif
    
    ofSetColor(255);
}

void cubeManagerMemory::drawTexturedCube(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max)
{
    ofPushMatrix();
//    ofTranslate(myCubes[i].position.x, myCubes[i].position.y);
//    ofRotate(myCubes[i].currentRot, 1, 0, 0);
//    ofDrawBox(0, 0, 0, myCubes[i].size, myCubes[i].size, myCubes[i].size);
    
    answerFullImage.bind();
    ofPushMatrix();
    
    ofTranslate(-myCubes[i].size/2, -myCubes[i].size/2, myCubes[i].size/2+0.1);
    GLfloat tx0 = texCoordX_min;
    GLfloat ty0 = texCoordY_min;
    GLfloat tx1 = texCoordX_max;
    GLfloat ty1 = texCoordY_max;
    
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
    answerFullImage.unbind();
    ofPopMatrix();
    
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







