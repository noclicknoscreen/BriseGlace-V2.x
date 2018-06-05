//
//  inputHandler.hpp
//  cubes
//
//  Created by Blindsp0t on 07/05/2018.
//
//

#ifndef inputHandler_hpp
#define inputHandler_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxSceneManager.h"

#include "player.h"
#include "cubeManagerHiddenWord.h"
#include "utils.h"
#include "enigmaManager.h"

#define movementSmoothingValue 15
#define spaceBetweenLetters 40


typedef struct
{
    string letter;
    ofPoint sourcePos, destination, currentPos;
    ofFloatColor textColor;
    float alpha;
    vector<int> correspondingCubes;
} letterElement;


class inputHandler
{
public:
    void setup(int _inputTextPosition);
    void getNewText(player _player);//int _userId, string txt);
    int update(cubeManager* cm);
    void draw();
    void compareInput(string wantedWord);
    void clearDuplicatesLettersHistory();
    void setRevealMode(){revealMode = true; currentRevealCube=0;}
    bool isReadyForNewText(){return readyForNewText;}
    void setReadyForNewText(){readyForNewText = true;}
    void setWordToFind(string _wantedWord);
    void revealTirrets(cubeManager* cm);
    
private:
    string text;
    ofTrueTypeFont font, fontBig;
    vector<letterElement> splittedString;
    int userId;
    vector<string> duplicatesLetters;
    
    int currentRevealLetter, currentRevealCube;
    bool revealMode;
    bool readyForNewText;
    
    string wordToFind;
    int nbCubesRotated;
    
    int mInputTextYPosition;
    
};

#endif /* inputHandler_hpp */
