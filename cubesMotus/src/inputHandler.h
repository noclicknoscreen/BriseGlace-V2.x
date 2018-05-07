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

#define inputTextYPosition 400
#define movementSmoothingValue 15
#define spaceBetweenLetters 15


typedef struct
{
    string letter;
    ofPoint sourcePos, destination, currentPos;
    ofColor textColor;
    float alpha;
} letterElement;


class inputHandler
{
public:
    void setup();
    void getNewText(int userId, string txt);
    void update();
    void draw();
    void compareInput(string wantedWord);
    
    
private:
    string text;
    ofTrueTypeFont font;
    vector<letterElement> splittedString;
};

#endif /* inputHandler_hpp */
