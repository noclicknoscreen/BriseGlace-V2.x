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
#include "utils.h"

#include "cubeManager.h"

class cubeManagerMemory : public cubeManager
{
    
    public :
    
    void setup(int _cubesPositionY, int _espacementCubes);
    void update(ofPoint _lightPos, int cubesRotationSpeed);
    void draw();
    void drawTexturedCube(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max);
    void setGrid(int _nbLines, int _nbRows);
    
    //cubes
    void rotateToWhite(int i);
    void rotateToWood(int i);
    void rotateToLetter(int i);
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
    
    int mNbLines, mNbRows;
    
    //consigne
    string consigne;
    float consigneWidth;
    
    // fbo to draw portion of image solution
    ofImage answerFullImage;
    
    // What is behind the cubes
private:
    string mContent;
public:
    string getContent(){return mContent;};
};


