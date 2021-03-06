//
//  inputHandler.hpp
//  cubes
//
//  Created by Blindsp0t on 07/05/2018.
//
//

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "ofxSceneManager.h"
#include "ofEvent.h"

#include "player.h"
#include "cubeManagerHiddenWord.h"
#include "utils.h"
#include "enigmaManager.h"

#define movementSmoothingValue 15
#define spaceBetweenLetters 80


typedef struct
{
    string letter;
//    ofPoint sourcePos, destination, currentPos;
    ofPoint destination, currentPos;
    ofFloatColor textColor;
    float alpha;
    vector<int> correspondingCubes;
} letterElement;


class inputHandler
{
public:
    void    setup(ofPoint _inputTextPosition, float _maxWidth, float _lineHeight);
    void    getNewText(player _player);
    int     update(cubeManager* cm, float alphaDecay);
    void    draw();
    
    void    setRevealMode(){revealMode = true; currentRevealCube=0;}
    bool    isReadyForNewText(){return mReadyForNewText;}
    void    setReadyForNewText(){mReadyForNewText = true;}
    void    revealTirrets(cubeManager* cm);
    
    // no root implementation
    virtual void    compareInput(string wantedWord) = 0;
    
    void resetInputs();
    void resetDuplicates();
    
    ofEvent<void> readyForNewText;
    
private:
    string text;
    ofTrueTypeFont font, fontBig;
    int userId;
    
    int currentRevealLetter, currentRevealCube;
    bool revealMode;
    bool mReadyForNewText;
    int nbCubesRotated;
    
    ofPoint mInputTextPosition;
    float   mMaxWidth;
    float   mLineHeight;
    
protected:
    string wordToFind;
    vector<letterElement> splittedString;
    vector<string> duplicatesLetters;
    
};
