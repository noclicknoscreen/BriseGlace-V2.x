//
//  cubeManager.cpp
//  cubes
//
//  Created by Blindsp0t on 03/05/2018.
//
//

#include "cubeManagerMemory.h"


void cubeManagerMemory::setup(ofPoint _cubesPos, int _espacementCubes, int _cubeSize)
{
    // Root Setup -----
    cubeManager::setup(_cubesPos, _espacementCubes, _cubeSize);
    // Do the grid --
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
    answerFullImage = bigEnigmaManager().getCurrentEnigma()->getImageSolution();
    answerFullImage.resize(_nbRows*cubeSize, _nbLines*cubeSize);
    
    // Shuffle the pseudo string
    bigEnigmaManager().setPseudoString(_nbRows * _nbLines);
    
    int countCube = 0;
    
    for(int idxRow=0; idxRow<_nbRows; idxRow++)
    {
        
        for(int idxLine=0; idxLine<_nbLines; idxLine++)
        {
            cube* tmpCube = new cube();
            int step = cubeSize + 2*mEspacementCubes;
            wstring rndLetter = bigEnigmaManager().pickPseudoLetter(countCube);
            
//            do{
//                rndLetter = utils::getRndLetter();
//            }while(ofStringTimesInString(mContent, rndLetter) > 0 && mContent != "");
            
            ofPoint position(mCubesPosition.x - 0.5*_nbRows*step + 0.5*step, mCubesPosition.y - 0.5*_nbLines*step + 0.5*step);
            position.x += idxRow*step;
            position.y += idxLine*step;
            position.z = mCubesPosition.z;
            
            tmpCube->setup(position, cubeSize);
            ofLog() << "Add cube , letter = "  << utils::toByteString(rndLetter);
            tmpCube->setLetter(rndLetter);
            tmpCube->rotateToLetter();
            
            mContent += utils::toByteString(rndLetter);
            
            myCubes.push_back(*tmpCube);
            countCube++;
            
        }
    }
    
}


//--------------------------------------------------------------
void cubeManagerMemory::draw(){

    // Enable all you need
    ofEnableDepthTest();
    ofEnableLighting();
    
    ofSetSmoothLighting(true);
//    spotLightCubes.enable();
    
    for(int idxCube=0; idxCube<myCubes.size(); idxCube++)
    {
        ofPushMatrix();
        
        
            ofTranslate(myCubes[idxCube].position.x, myCubes[idxCube].position.y, myCubes[idxCube].position.z);
            ofRotate(myCubes[idxCube].currentRot, 1.0, 0.0, 0.0);
        
            materialColor.setHue(0);
            material.setAmbientColor(materialColor);
            material.setDiffuseColor(materialColor);
            //material.setSpecularColor(materialColor);

            // Tout le cube est en bois --------
            material.begin();
            ofEnableNormalizedTexCoords();
            textureBois.bind();
               ofDrawBox(myCubes[idxCube].size, myCubes[idxCube].size ,myCubes[idxCube].size);
            material.end();
            textureBois.unbind();
            
            // FACE AVEC IMAGE --------------------------------------------------
            ofPushMatrix();
            material.begin();
            material.setAmbientColor(myCubes[idxCube].getMaterialColor());
            material.setDiffuseColor(ofColor(myCubes[idxCube].getMaterialColor(), 140)); //add some transparency here, to keep the texture visible ;)
        
        
            int row = idxCube % mNbRows;
            int line = idxCube / mNbLines;
        
//            ofLog() << "We draw a cutted image [line, row] = [" << line << "," << row << "]";
        
            ofDisableNormalizedTexCoords();
            drawTexturedCube(&answerFullImage,
                             idxCube,
                             (float)line / (float)mNbRows,
                             (float)(line+1) / (float)mNbRows,
                             (float)row / (float)mNbLines,
                             (float)(row+1) / (float)mNbLines
                             );
        
            material.end();
            ofPopMatrix();
            // END FACE AVEC IMAGE --------------------------------------------------
        
            // FACE DE COULEUR --------------------------------------------------
            material.begin();
        
            // La couleur du cube est blanche ou de couleur selon la bonne réponse
            material.setAmbientColor(myCubes[idxCube].getMaterialColor());
            material.setDiffuseColor(ofColor(myCubes[idxCube].getMaterialColor(), 140)); //add some transparency here, to keep the texture visible ;)
        
            ofEnableNormalizedTexCoords();
            for(int i=0; i<myCubes.size(); i++)
            {
                ofPushMatrix();
                ofRotate(180,1,0,0);
                ofDrawRectangle(-myCubes[i].size/2, -myCubes[i].size/2, (myCubes[i].size/2)+0.5, myCubes[i].size, myCubes[i].size);
                ofPopMatrix();
            }
            material.end();
            // END FACE DE COULEUR --------------------------------------------------
        
            // DEBUT LETTRE ------------------------------------------------
            float textHeight, textWidth;
            textWidth = font.getStringBoundingBox("A", 0, 0).getWidth();
            textHeight = font.getStringBoundingBox("A", 0, 0).getHeight();
            
            ofSetColor(0);
            
            ofPushMatrix();
            
                ofTranslate(-textWidth/2, -textHeight/2, -1.0f * (1 + myCubes[idxCube].size/2));
                ofRotate(180,0,1,0);
                ofRotate(180,0,0,1);

        font.drawString(utils::toUpperCase(utils::toByteString(myCubes[idxCube].getLetter())), 0, 0);
        
            ofPopMatrix();
            // FIN LETTRE --------------------------------------------------
        
        ofPopMatrix();

        
    }

    // DEBUG DRAW
#if defined DRAW_DEBUG
    spotLight.draw();
#endif
    
//    spotLightCubes.disable();
//    ofDisableLighting();
    

    
    ofSetColor(255);
}

//void cubeManagerMemory::drawTexturedCube(ofImage *texture, int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max)
//{
//    float realTexCoordX_min = texCoordX_min * texture->getWidth();
//    float realTexCoordX_max = texCoordX_max * texture->getWidth();
//    float realTexCoordY_min = texCoordY_min * texture->getHeight();
//    float realTexCoordY_max = texCoordY_max * texture->getHeight();
//    
//    
//    ofPushMatrix();
////    ofTranslate(myCubes[i].position.x, myCubes[i].position.y);
////    ofRotate(myCubes[i].currentRot, 1, 0, 0);
////    ofDrawBox(0, 0, 0, myCubes[i].size, myCubes[i].size, myCubes[i].size);
//    
//    texture->bind();
//    
//    ofPushMatrix();
//    
//    ofTranslate(-myCubes[i].size/2, -myCubes[i].size/2, myCubes[i].size * (0.5+0.005));
//    GLfloat tx0 = realTexCoordX_min;
//    GLfloat ty0 = realTexCoordY_min;
//    GLfloat tx1 = realTexCoordX_max;
//    GLfloat ty1 = realTexCoordY_max;
//    
//    GLfloat px0 = 0.0f;
//    GLfloat py0 = 0.0f;
//    GLfloat px1 = myCubes[i].size;
//    GLfloat py1 = myCubes[i].size;
//    
//    GLfloat tex_coords[] = {
//        tx0,ty0,
//        tx1,ty0,
//        tx1,ty1,
//        tx0,ty1
//    };
//    GLfloat verts[] = {
//        px0,py0,
//        px1,py0,
//        px1,py1,
//        px0,py1
//    };
//    
//    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
//    glTexCoordPointer(2, GL_FLOAT, 0, tex_coords );
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(2, GL_FLOAT, 0, verts );
//    glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
//    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
//    
//    
//    ofPopMatrix();
//    
//    ofSetColor(255);
//    texture->unbind();
//    ofPopMatrix();
//    
//}

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







