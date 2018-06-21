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
    
    void setup(ofPoint _cubesPos, int _espacementCubes, int _cubeSize);
//    void update(ofPoint _lightPos, int cubesRotationSpeed);
    void draw();
    void getWord(wstring word);
    
    int getNumberOfCubes() {return myCubes.size();}
    
private:
    
    //consigne
    string consigne;
    float consigneWidth;

};
