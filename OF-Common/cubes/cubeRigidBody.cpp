//
//  cubeRigidBody.cpp
//  theEnigmaTest
//
//  Created by Sébastien Albert on 18/06/2018.
//
//

#include "cubeRigidBody.h"

void cubeRigidBody::customDraw(ofColor _winnerColor)
{
    transformGL();
    
    ofPushMatrix();
    ofRotate(-90, 1, 0, 0);
    
    ofVec3f size = getSize();
    
    //apply texture
    ofEnableNormalizedTexCoords();
    texture.bind();
    
    //3d box
    ofSetColor(255);
    
    ofFill();
    ofDrawBox(0, 0, 0, size.x, size.y, size.z);
    
    texture.unbind();
    ofDisableNormalizedTexCoords();
    
    
    //letter
    float textHeight, textWidth;
    textWidth = font.getStringBoundingBox(letter, 0, 0).getWidth();
    textHeight = font.getStringBoundingBox(letter, 0, 0).getHeight();
    
    
    
    if(_winnerColor != ofColor::white)
    {
        ofPushMatrix();
        
        materialForFaceColor.setAmbientColor(_winnerColor);
        materialForFaceColor.setDiffuseColor(ofColor(_winnerColor, 200));
        
        materialForFaceColor.begin();
        
        ofTranslate(0,0, size.z/2 + 1);
        ofDrawRectangle(-size.x/2, -size.y/2, size.x, size.y);
        
        materialForFaceColor.end();
        ofSetColor(255);
        
        ofPopMatrix();
    }
    
    
    ofSetColor(0);
    
    // DRAW A LETTER ////////////////////////////////////////////////////
    ofPushMatrix();
    ofRotate(180, 0, 0, 1);
    ofRotate(180, 0, 1, 0);
    ofRotate(180, 1, 0, 0);
    
    ofTranslate(-textWidth/2.0,  -textHeight/2, float(size.z/2 +2));
    
    ofDisableLighting();
    font.drawString(letter, 0, 0);
    ofEnableLighting();
    ofPopMatrix();
    
    // DRAW A LETTER ////////////////////////////////////////////////////
    ofPushMatrix();
    //            ofRotate(180, 0, 0, 1);
    //            ofRotate(180, 0, 1, 0);
    //            ofRotate(180, 1, 0, 0);
    
    ofTranslate(-textWidth/2.0,  -textHeight/2, -1.0f *     float(size.z/2 +2));
    
    ofDisableLighting();
    font.drawString(letter, 0, 0);
    ofEnableLighting();
    ofPopMatrix();
    
    ofPopMatrix();
    
    //restore gl state
    restoreTransformGL();
    
    
    
    
}

void cubeRigidBody::setLetter(string _letter)
{
    letter = _letter;
}

void cubeRigidBody::setTexture(ofImage _texture)
{
    texture = _texture;
}

void cubeRigidBody::setup(ofImage _image, string _letter)
{
    setTexture(_image);
    setLetter(_letter);
    font.load(globalFontName, globalFontSizeMedium);
    
    //setSize(_size);
}
