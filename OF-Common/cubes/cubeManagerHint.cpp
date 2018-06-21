//
//  cubeManager.cpp
//  cubes
//
//  Created by Blindsp0t on 03/05/2018.
//
//

#include "cubeManagerHint.h"


void cubeManagerHint::setup(ofPoint _cubesPos, int _espacementCubes, int _cubeSize)
{
    // Root Setup -----
    cubeManager::setup(_cubesPos, _espacementCubes, 100);
    // Do the grid --
    setGrid(4,4);
    //
};

void cubeManagerHint::setGrid(int _nbLines, int _nbRows){
    
    // Flush all cubes
    myCubes.clear();
    mContent = "";
    
    // Set the shape (how many lines and rows)
    mNbLines = _nbLines;
    mNbRows = _nbRows;
    
    // load the big image
    // Push a new hint
    bigEnigmaManager().pushHintIndex();
    
    answerFullImage = bigEnigmaManager().getCurrentEnigma()->getImage(bigEnigmaManager().pickHintIndex());
    answerFullImage.resize(_nbRows*cubeSize, _nbLines*cubeSize);
    
    //load font
    textFbo.allocate(_nbRows*cubeSize, _nbLines*cubeSize);
    textFbo.setUseTexture(true);
    
    //wrap text
    myText.init(globalFontName, globalFontSizeMedium);
    myText.setText(bigEnigmaManager().getCurrentEnigma()->getTitre(bigEnigmaManager().pickHintIndex()));
    myText.wrapTextArea(0.75 * cubeSize * _nbRows, 0.75 * cubeSize * _nbLines);
    
    //fill fbo and put it into an image
    textFbo.begin();
    ofClear(255);
    ofSetColor(0);
    myText.setColor(0, 0, 0, 255);
    myText.drawCenter(0.5 * cubeSize * _nbRows, 0.25 * cubeSize * _nbLines);
    //    ofDrawCircle(0, 0, 10);
    textFbo.end();
    
    //put fbo in an image
    ofPixels tmp;
    textFbo.readToPixels(tmp);
    textImageFromFbo.setFromPixels(tmp);
    
    for(int idxRow=0; idxRow<_nbRows; idxRow++)
    {
        
        for(int idxLine=0; idxLine<_nbLines; idxLine++)
        {
            cube* tmpCube = new cube();
            int step = cubeSize + 2*mEspacementCubes;
//            string rndLetter;
//            do{
//                rndLetter = utils::getRndLetter();
//            }while(ofStringTimesInString(mContent, rndLetter) > 0 && mContent != "");
            
            ofPoint position(mCubesPosition.x - 0.5*_nbRows*step + 0.5*step, mCubesPosition.y - 0.5*_nbLines*step + 0.5*step);
            position.x += idxRow*step;
            position.y += idxLine*step;
            position.z = mCubesPosition.z;
            
            tmpCube->setup(position, cubeSize);
//            tmpCube->setLetter(rndLetter);
            tmpCube->rotateToWhite();
            
//            mContent += rndLetter;
            
            myCubes.push_back(*tmpCube);
            
        }
    }
    
}


//--------------------------------------------------------------
void cubeManagerHint::draw(){
    
    // Enable all you need
    ofEnableDepthTest();
    ofEnableLighting();
    
//    cam.setPosition(0, 0, -2000);
//    cam.begin();
//    
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
            ofDrawBox(myCubes[idxCube].size, myCubes[idxCube].size, myCubes[idxCube].size);
        material.end();
        textureBois.unbind();
        
        // FACE AVEC IMAGE (Indice) --------------------------------------------------
//        ofPushMatrix();
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
//        ofPopMatrix();
        // END FACE BLANCHE --------------------------------------------------
        
        // FACE BLANCHE --------------------------------------------------
        material.begin();
        material.setAmbientColor(myCubes[idxCube].getMaterialColor());
        material.setDiffuseColor(ofColor(myCubes[idxCube].getMaterialColor(), 140)); //add some transparency here, to keep the texture visible ;)
        
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
        
        // FACE AVEC IMAGE (fbo text) --------------------------------------------------
        ofPushMatrix();
        ofRotate(myCubes[idxCube].currentRot+180, 1, 0, 0);
        material.begin();
        material.setAmbientColor(myCubes[idxCube].getMaterialColor());
        material.setDiffuseColor(ofColor(myCubes[idxCube].getMaterialColor(), 140)); //add some transparency here, to keep the texture visible ;)
        
        //            ofLog() << "We draw a cutted image [line, row] = [" << line << "," << row << "]";
        
        ofDisableNormalizedTexCoords();
        drawTexturedCube(&textImageFromFbo,
                         idxCube,
                         (float)line / (float)mNbRows,
                         (float)(line+1) / (float)mNbRows,
                         (float)row / (float)mNbLines,
                         (float)(row+1) / (float)mNbLines
                         );
        
        material.end();
        ofPopMatrix();
        // END FACE BLANCHE --------------------------------------------------
        
        ofPopMatrix();
        
        
    }
    
    // DEBUG DRAW
#if defined DRAW_DEBUG
    spotLight.draw();
#endif
    
    //    spotLightCubes.disable();
    ofDisableLighting();

//    cam.end();
    
}

//void cubeManagerHint::drawTexturedCube(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max)
//{
//    ofPushMatrix();
//    //    ofTranslate(myCubes[i].position.x, myCubes[i].position.y);
//    //    ofRotate(myCubes[i].currentRot, 1, 0, 0);
//    //    ofDrawBox(0, 0, 0, myCubes[i].size, myCubes[i].size, myCubes[i].size);
//    
//    answerFullImage.bind();
//    ofPushMatrix();
//    
//    ofTranslate(-myCubes[i].size/2, -myCubes[i].size/2, myCubes[i].size/2+0.1);
//    GLfloat tx0 = texCoordX_min;
//    GLfloat ty0 = texCoordY_min;
//    GLfloat tx1 = texCoordX_max;
//    GLfloat ty1 = texCoordY_max;
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
//    answerFullImage.unbind();
//    ofPopMatrix();
//    
//}


//void cubeManagerHint::drawLetteredCube(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max)
//{
//    ofPushMatrix();
//    ofRotate(myCubes[i].currentRot+180, 1, 0, 0);
//    
//    //    ofTranslate(myCubes[i].position.x, myCubes[i].position.y);
//    //    ofRotate(myCubes[i].currentRot, 1, 0, 0);
//    //    ofDrawBox(0, 0, 0, myCubes[i].size, myCubes[i].size, myCubes[i].size);
//    
//    textImageFromFbo.bind();
//    ofPushMatrix();
//    
//    ofTranslate(-myCubes[i].size/2, -myCubes[i].size/2, myCubes[i].size/2+0.1);
//    GLfloat tx0 = texCoordX_min;
//    GLfloat ty0 = texCoordY_min;
//    GLfloat tx1 = texCoordX_max;
//    GLfloat ty1 = texCoordY_max;
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
//    textImageFromFbo.unbind();
//    ofPopMatrix();
//    
//}

void cubeManagerHint::rotateToWhite(int i)
{
    myCubes[i].rotateToWhite();
}

void cubeManagerHint::rotateToWood(int i)
{
    myCubes[i].rotateToWood();
}

void cubeManagerHint::rotateToLetter(int i)
{
    myCubes[i].rotateToLetter();
}







