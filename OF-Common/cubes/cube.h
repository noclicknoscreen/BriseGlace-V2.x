//
//  cube.hpp
//  cubes
//
//  Created by Blindsp0t on 03/05/2018.
//
//

#ifndef cube_hpp
#define cube_hpp

#include <stdio.h>
#include "ofMain.h"
#include "utils.h"

class cube
{
public:
    void setup(ofPoint pos, float size);
    void update(float _rotationSpeed);
    void rotateToWhite();
    void rotateToWood();
    void rotateToLetter();
    
    
    float currentRot, desiredRot;
    ofPoint position;
    float size;
//    bool letterFace, whiteFace, woodFace;
    
//    char myLetter;
    bool isRotating;
    
private:
    ofColor materialColor;
public:
    void setMaterialColor(ofColor _color){materialColor = _color;};
    ofColor getMaterialColor(){return materialColor;};
    
private:
    wstring mLetter;
public:
    void setLetter(wstring letter);
    wstring getLetter();
    
};
#endif /* cube_hpp */
