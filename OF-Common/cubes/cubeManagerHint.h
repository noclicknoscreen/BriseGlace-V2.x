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
#include "ofxTextBlock.h"

#include "cubeManager.h"

class cubeManagerHint : public cubeManager
{
    
    public :
    
    void setup(ofPoint _cubesPos, int _espacementCubes, int _cubeSize);
//    void update(ofPoint _lightPos, int cubesRotationSpeed);
    void draw();
//    void drawTexturedCube(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max);
//    void drawLetteredCube(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max);
    void setGrid(int _nbLines, int _nbRows);
    
    //cubes
    void rotateToWhite(int i);
    void rotateToWood(int i);
    void rotateToLetter(int i);
    int getNumberOfCubes() {return myCubes.size();}
    
private:
    
    int mNbLines, mNbRows;
    
    //consigne
    string consigne;
    float consigneWidth;
    
    // fbo to draw portion of image solution
    ofImage answerFullImage;
    
    //fbo to draw text, to be used as texture
    ofFbo textFbo;
    ofImage textImageFromFbo;
    
    //text
    ofxTextBlock myText;
    
    // What is behind the cubes
private:
    string mContent;
public:
    string getContent(){return mContent;};

};


