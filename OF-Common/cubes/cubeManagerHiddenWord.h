//
//  cubeManagerHiddenWord.hpp
//  cubes
//
//  Created by Blindsp0t on 03/05/2018.
//
//

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "cube.h"
#include "utils.h"

#include "cubeManager.h"

class cubeManagerHiddenWord  : public cubeManager
{
    
    public :
    
    void setup(int _cubesPositionY, int _espacementCubes);
    void update(ofPoint _lightPos, int cubesRotationSpeed);
    void draw();
    void getWord(string word);
    
    int getNumberOfCubes() {return myCubes.size();}
    
private:
    
    //lumiere
    ofLight spotLight;
    ofColor lightColor;
    ofColor materialColor;
    ofMaterial material;
    
    //police de caracteres
    ofTrueTypeFont              font;
    
    //texture
    ofImage                     texture;
    
    //cubes size
    float                       cubeSize;
    
    //consigne
    string consigne;
    float consigneWidth;

};
