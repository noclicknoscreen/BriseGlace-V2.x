//
//  indice.cpp
//  emptyExample
//
//  Created by Blindsp0t on 09/05/2018.
//
//

#include "indice.h"
#include "cube.h"


//void indice::setup(string photoFilename)
void indice::setup()
{
    
    ofEnableDepthTest();
    
    ofLogNotice() << "Indice setup : [texte] : [" << bigEnigmaManager().getCurrentEnigma()->getTitre(HINT1);
    //load texture
    texture = bigEnigmaManager().getCurrentEnigma()->getImage(HINT1);
    texture.resize(3*cubeSize, 3*cubeSize);

    cubeSize = 120;
    totalWidth = cubeSize * 3;
    yPos = ofGetHeight()/2 - 3*(cubeSize/2);
    
    // Empty cubes
    myCubes.clear();
    
    //create cubes
    for(int i=0; i<9; i++)
    {
        int line = i%3;
        int row = i/3;
        
        if(i%3 == 0)
            yPos+= cubeSize;
        
        ofPoint pos = ofPoint((ofGetWidth()-totalWidth)/2 + (i%3)*cubeSize + cubeSize/2, yPos);
        
        cube c;
        c.setup(pos, cubeSize);
        c.currentRot = 180;
        c.desiredRot = 180;
        myCubes.push_back(c);
    }
    
    cubeIndex = 0;
    revealMode = false;
    
    //load font
    textFbo.allocate(3*cubeSize, 3*cubeSize);
    textFbo.setUseTexture(true);
    
    
    //wrap text
    myText.init(globalFontName, globalFontSizeMedium);
    myText.setText(bigEnigmaManager().getCurrentEnigma()->getTitre(bigEnigmaManager().pickHintIndex()));
    myText.wrapTextX(cubeSize*3);
    
    //fill fbo and put it into an image
    textFbo.begin();
    ofClear(255);
    ofSetColor(0);
    myText.setColor(0, 0, 0, 255);
    myText.drawCenter(cubeSize*1.5, 0);
//    ofDrawCircle(0, 0, 10);
    textFbo.end();
    
    //put fbo in an image
    ofPixels tmp;
    textFbo.readToPixels(tmp);
    textImageFromFbo.setFromPixels(tmp);
    
    //lumiere
    ofEnableLighting();
    spotLight.setSpotlight();
    spotLight.setSpotlightCutOff(200);
    spotLight.setAttenuation(0.3,0,0); //puissance de la light = inverse de l'attenuation
    spotLight.setSpotConcentration(0.15);
    spotLight.setDiffuseColor( ofColor(255.f, 255.f, 255.f));
    spotLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    material.setShininess( 128);
    lightColor.setBrightness( 255.0f);
    lightColor.setSaturation( 0.f );
    materialColor.setBrightness(255);
    materialColor.setSaturation(0);


}

void indice::update()
{
    //reveal corresponding cubes
    if(revealMode)
    {
        bool someoneRotating = false;
        for(int i=0; i<myCubes.size(); i++)
        {
            if(myCubes[i].isRotating == true)
                someoneRotating = true;
        }
        
        if(!someoneRotating)
        {
            if(cubeIndex < myCubes.size())
            {
                cubeIndex++;
                myCubes[cubeIndex-1].rotateToWhite();
            }
        }
    }
    
    // update cubes
    for(int i=0; i<myCubes.size(); i++)
    {
        myCubes[i].update(5);
    }
    
    //lumiere
    spotLight.setPosition(ofGetWidth()*5/6, ofGetHeight()/2,150);
    spotLight.setOrientation( ofVec3f( 0, 45, 30) );
    lightColor.setHue(0);
    spotLight.setDiffuseColor(lightColor);
    material.setSpecularColor(materialColor);
}

void indice::draw()
{
    ofEnableLighting();
    ofSetSmoothLighting(true);
    spotLight.enable();
    
    materialColor.setHue(0);
    material.setAmbientColor(materialColor);
    material.setDiffuseColor(materialColor);
    material.begin();
   
    
    for(int i=0; i<myCubes.size(); i++)
    {
        int line = i%3;
        int row = i/3;
        
        ofDisableNormalizedTexCoords();
        drawTexturedCube(i,
                         float(line*texture.getWidth()/3),
                         float((line+1)*texture.getWidth()/3),
                         float(row*texture.getHeight()/3),
                         float((row+1)*texture.getHeight()/3)
                         );
        
        drawTexturedCubeTEXT(i,
                             float(line*textImageFromFbo.getWidth()/3),
                             float((line+1)*textImageFromFbo.getWidth()/3),
                             float(row*textImageFromFbo.getHeight()/3),
                             float((row+1)*textImageFromFbo.getHeight()/3)
                             );
    }
    
    material.end();
//    spotLight.disable();
//    ofDisableLighting();
    //spotLight.draw();
   
}


void indice::drawTexturedCube(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max)
{
    ofPushMatrix();
        ofTranslate(myCubes[i].position.x, myCubes[i].position.y);
        ofRotate(myCubes[i].currentRot, 1, 0, 0);
        ofDrawBox(0, 0, 0, myCubes[i].size, myCubes[i].size, myCubes[i].size);
      
        texture.bind();
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
        texture.unbind();
    ofPopMatrix();

}


void indice::drawTexturedCubeTEXT(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max)
{
    ofPushMatrix();
        ofTranslate(myCubes[i].position.x, myCubes[i].position.y);

        
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
        
        ofPushMatrix();
            ofRotate(myCubes[i].currentRot+180, 1, 0, 0);
            
            textImageFromFbo.getTexture().bind();
            ofPushMatrix();
            
            ofTranslate(-myCubes[i].size/2, -myCubes[i].size/2, (myCubes[i].size+0.1)/2);
            
            
            glEnableClientState( GL_TEXTURE_COORD_ARRAY );
            glTexCoordPointer(2, GL_FLOAT, 0, tex_coords );
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(2, GL_FLOAT, 0, verts );
            glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
            glDisableClientState( GL_TEXTURE_COORD_ARRAY );
            
            
            ofPopMatrix();
            ofSetColor(255);
            textImageFromFbo.getTexture().unbind();
        ofPopMatrix();
    
    ofPopMatrix();
    
    
}




