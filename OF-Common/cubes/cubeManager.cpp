//
//  cubeManager.cpp
//  theBigGame
//
//  Created by Sébastien Albert on 04/06/2018.
//
//

#include "cubeManager.h"


void cubeManager::setup(int _cubesPositionY, int _espacementCubes)
{
    
    mCubesPositionY = _cubesPositionY;
    mEspacementCubes = _espacementCubes;

}


void cubeManager::colorizeCube(int cubeId, ofColor _color)
{
    myCubes[cubeId].setMaterialColor(_color);
}
