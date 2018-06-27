//
//  cubeRigidBody.hpp
//  theEnigmaTest
//
//  Created by Sébastien Albert on 18/06/2018.
//
//

#pragma once

#include "ofxBullet.h"
#include "utils.h"

class cubeRigidBody : public ofxBulletBox
{
    ofImage texture;
    ofTrueTypeFont font;
    
    ofMaterial materialForFaceColor;
    
public:
    void customDraw(ofColor _winnerColor=ofColor::white);
    
    void setTexture(ofImage _texture);
    void setup(ofImage _image, wstring _letter);
    
private:
    void drawALetter(float _rotX, float _rotY, float _rotZ, ofColor _color = ofColor::black);
    
private:
    wstring mLetter;
public:
    void setLetter(wstring letter);
    wstring getLetter();
    
private:
    bool        mIsInAnswer;
    ofColor     mFoundPlayerColor;
public:
    void setIsInAnwer(bool _isInAnswer, ofColor _foundPlayerColor);

};


