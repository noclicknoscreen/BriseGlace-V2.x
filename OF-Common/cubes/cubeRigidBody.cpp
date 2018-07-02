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
    ofFill();
    ofSetColor(255);
    
    if(mIsInAnswer == false){
        // LE CUBE N'A PAS ENCORE ETE MENTIONNE
        materialForFaceColor.setAmbientColor(ofFloatColor(0.2));
        materialForFaceColor.setDiffuseColor(ofFloatColor(0.8));
        
    }else{
        
        // LE CUBE A ETE MENTIONNE
        materialForFaceColor.setAmbientColor(mFoundPlayerColor);
        materialForFaceColor.setDiffuseColor(mFoundPlayerColor);
        
    }
    
    materialForFaceColor.begin();
    texture.bind();
    
    ofDrawBox(0, 0, 0, size.x, size.y, size.z);
    materialForFaceColor.end();
    
    texture.unbind();
    ofDisableNormalizedTexCoords();
    
    
    //    //letter
    //    float textHeight, textWidth;
    //    textWidth = font.getStringBoundingBox(utils::toByteString(mLetter), 0, 0).getWidth();
    //    textHeight = font.getStringBoundingBox(utils::toByteString(mLetter), 0, 0).getHeight();
    //
    
    
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
    
    if(mIsInAnswer == false){
        
        // LE CUBE N'A PAS ENCORE ETE MENTIONNE
        drawALetter(180, 0, 0);
        drawALetter(0, 0, 0);
        
    }else{

        // LE CUBE A ETE MENTIONNE
        // On dessine une lettre sur chaque face
        drawALetter(0, 0, 0);
        drawALetter(90, 0, 0);
        drawALetter(180, 0, 0);
        drawALetter(270, 0, 0);
        drawALetter(0, 90, 90);
        drawALetter(0, 270, 90);
        
    }
    
    ofPopMatrix();
    //restore gl state
    restoreTransformGL();
    
    
}

void cubeRigidBody::drawALetter(float _rotX, float _rotY, float _rotZ, ofColor _color){
    
    //letter
    float textHeight, textWidth;
    textWidth = font.getStringBoundingBox(utils::toByteString(mLetter), 0, 0).getWidth();
    textHeight = font.getStringBoundingBox(utils::toByteString(mLetter), 0, 0).getHeight();
    
    ofVec3f size = getSize();
    
    ofPushMatrix();
    ofPushStyle();
    
    ofRotateX(_rotX);
    ofRotateY(_rotY);
    ofRotateZ(_rotZ);
    
    //    ofRotate(180, 0, 0, 1);
    //    ofRotate(180, 0, 1, 0);
    //    ofRotate(180, 1, 0, 0);
    
    ofTranslate(-textWidth/2.0, -textHeight/2, float(size.z/2 +2));
    
    ofDisableLighting();
    ofSetColor(_color);
    font.drawString(utils::toUpperCase(utils::toByteString(mLetter)), 0, 0);
    ofEnableLighting();
    
    ofPopStyle();
    ofPopMatrix();
}

void cubeRigidBody::setLetter(wstring _letter)
{
    mLetter = _letter;
}
wstring cubeRigidBody::getLetter()
{
    return mLetter;
}

void cubeRigidBody::setTexture(ofImage _texture)
{
    texture = _texture;
}

void cubeRigidBody::setup(ofImage _image, wstring _letter)
{
    setTexture(_image);
    setLetter(_letter);
    font.load(globalFontName, globalFontSizeMedium);
    
    //setSize(_size);
}

void cubeRigidBody::setIsInAnwer(bool _isInAnswer, ofColor _foundPlayerColor){
    mIsInAnswer = _isInAnswer;
    mFoundPlayerColor = _foundPlayerColor;

}


