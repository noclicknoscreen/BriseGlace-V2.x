//
//  cubeManager.hpp
//  theBigGame
//
//  Created by Sébastien Albert on 04/06/2018.
//
//

#pragma once

#include "cube.h"

class cubeManager
{
    
    
protected :
    void setup(int _cubesPositionY, int _espacementCubes);

    int mCubesPositionY;
    int mEspacementCubes;
    
public:
    vector<cube>                myCubes;
    
    void colorizeCube(int cubeId, ofColor _color);
    
};
