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
#include "cubeManager.h"
#include "player.h"

#define inputTextYPosition 400
#define movementSmoothingValue 15
#define spaceBetweenLetters 15


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
    void setup();
    void getNewText(player _player);//int _userId, string txt);
    bool update(cubeManager* cm);
    void draw();
    void compareInput(string wantedWord);
    void clearDuplicatesLettersHistory();
    void setRevealMode(){revealMode = true; currentRevealCube=0;}
    bool isReadyForNewText(){return readyForNewText;}
    void setReadyForNewText(){readyForNewText = true;}
    
private:
    string text;
    ofTrueTypeFont font;
    vector<letterElement> splittedString;
    int userId;
    vector<string> duplicatesLetters;
    
    int currentRevealLetter, currentRevealCube;
    bool revealMode;
    bool readyForNewText;
    
    string wordToFind;
    int nbCubesRotated;
    
};

#endif /* inputHandler_hpp */
