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



void cubeManager::rotateToWhite(int _idxCube)
{
    myCubes[_idxCube].rotateToWhite();
}

void cubeManager::rotateToWood(int _idxCube)
{
    myCubes[_idxCube].rotateToWood();
}

void cubeManager::rotateToLetter(int _idxCube)
{
    myCubes[_idxCube].rotateToLetter();
}

void cubeManager::rotateAllToWhite()
{
    for(int idxCube = 0; idxCube < myCubes.size(); idxCube++){
        myCubes[idxCube].rotateToWhite();
    }
}

void cubeManager::rotateAllToWood()
{
    for(int idxCube = 0; idxCube < myCubes.size(); idxCube++){
        myCubes[idxCube].rotateToWood();
    }
}

void cubeManager::rotateAllToLetter()
{
    for(int idxCube = 0; idxCube < myCubes.size(); idxCube++){
        myCubes[idxCube].rotateToLetter();
    }
}
