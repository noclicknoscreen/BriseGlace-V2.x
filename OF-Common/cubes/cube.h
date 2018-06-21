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

class cube
{
public:
    void setup(ofPoint pos, float size);
    void update(int rotationSpeed);
    void setLetter(char letter);
    void rotateToWhite();
    void rotateToWood();
    void rotateToLetter();
    
    
    float currentRot, desiredRot;
    ofPoint position;
    float size;
//    bool letterFace, whiteFace, woodFace;
//    string myLetter;
    char myLetter;
    bool isRotating;
    
private:
    ofColor materialColor;
public:
    void setMaterialColor(ofColor _color){materialColor = _color;};
    ofColor getMaterialColor(){return materialColor;};
    
};
#endif /* cube_hpp */
