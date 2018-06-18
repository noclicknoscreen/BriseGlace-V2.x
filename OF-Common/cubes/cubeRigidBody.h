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
    string letter;
    ofImage texture;
    ofTrueTypeFont font;
    
    ofMaterial materialForFaceColor;
    
public:
    void customDraw(ofColor _winnerColor=ofColor::white);
    
    void setLetter(string _letter);
    void setTexture(ofImage _texture);
    void setup(ofImage _image, string _letter, float _size);
};


