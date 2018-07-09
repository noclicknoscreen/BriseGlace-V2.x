//
//  cube.cpp
//  cubes
//
//  Created by Blindsp0t on 03/05/2018.
//
//

#include "cube.h"


void cube::setup(ofPoint _position, float _size)
{
    position = _position;
    size = _size;
    currentRot = 0;
    desiredRot = 0;
    
    isRotating = false;
};

void cube::update(float _rotationSpeed)
{
    //apparition suivant Z
    if(position.z < -150)
    {
        position.z += 1;
    }
    
    //rotation vers la face désirée
    if(currentRot < desiredRot)
    {
        isRotating = true;
        if(currentRot + _rotationSpeed <= desiredRot)
        {
            currentRot += _rotationSpeed;
        }
        else{
//            currentRot += (currentRot - desiredRot);
             currentRot = desiredRot;
        }
        
    }else{
        isRotating = false;
    }
    
};

void cube::rotateToWhite()
{
    if(isRotating == false){
        
        isRotating = true;
        
        if(int(currentRot)%360 == 0) //white
            desiredRot += 0;
        
        if(int(currentRot)%360 == 90) //wood
            desiredRot += 270;
        
        if(int(currentRot)%360 == 180) //letter
            desiredRot += 180;
    }
    
};//0


void cube::rotateToWood()
{
    
    if(isRotating == false){
        
        isRotating = true;
        
        if(int(currentRot)%360 == 0) //white
            desiredRot += 90;
        
        if(int(currentRot)%360 == 90) //wood
            desiredRot += 0;
        
        if(int(currentRot)%360 == 180) //letter
            desiredRot += 270;
    }
};

void cube::rotateToLetter()
{
    if(isRotating == false){
        
        isRotating = true;
        
        if(int(currentRot)%360 == 0) //white
            desiredRot += 180;
        
        if(int(currentRot)%360 == 90) //wood
            desiredRot += 90;
        
        if(int(currentRot)%360 == 180) //letter
            desiredRot += 0;
    }
};

void cube::setLetter(wstring _letter)
{
    mLetter = _letter;
}
wstring cube::getLetter()
{
    return mLetter;
}

