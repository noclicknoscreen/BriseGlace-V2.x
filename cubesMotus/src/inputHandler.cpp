//
//  inputHandler.cpp
//  cubes
//
//  Created by Blindsp0t on 07/05/2018.
//
//

#include "inputHandler.h"

void inputHandler::setup()
{
    font.load("Avenir.ttc", 24);
}

void inputHandler::getNewText(int userId, string txt)
{
    cout << "got new input from user " << userId << " : " << txt << endl;
    text = txt;
    
    ofPoint source;
    ofColor textColor;
    
    switch(userId)
    {
        case 0:
            source = ofPoint(0, ofGetHeight());
            textColor = ofColor::green;
            break;
        case 1:
            source = ofPoint(ofGetWidth()/2, ofGetHeight());
            textColor = ofColor::red;
            break;
        case 2:
            source = ofPoint(ofGetWidth(), ofGetHeight());
            textColor = ofColor::blue;
            break;
        default:
            textColor = ofColor::black;
            break;
    }
    
    splittedString.clear();
    float cumulatedOffset = 0;
    
    for(int i=0; i<text.size(); i++)
    {
        letterElement elt;
        elt.letter = ofToString(text[i]);
        elt.textColor = textColor;
        
        elt.sourcePos = source;
        elt.currentPos = source;
        elt.destination = ofPoint(cumulatedOffset + ofGetWidth()/2 - font.getStringBoundingBox(text, 0, 0).getWidth(), inputTextYPosition);
        
        elt.alpha = 255;
        
        cumulatedOffset += font.getStringBoundingBox(elt.letter, 0, 0).getWidth() + spaceBetweenLetters;
        
        splittedString.push_back(elt);
    }
}

void inputHandler::draw()
{
    for(int i=0; i<splittedString.size(); i++)
    {
        ofSetColor(splittedString[i].textColor);
        font.drawString(splittedString[i].letter, splittedString[i].currentPos.x, splittedString[i].currentPos.y);
    }
}

void inputHandler::update()
{
    for(int i=0; i<splittedString.size(); i++)
    {
        //movement to center
        if(splittedString[i].currentPos != splittedString[i].destination)
        {
            splittedString[i].currentPos += (splittedString[i].destination - splittedString[i].currentPos)/movementSmoothingValue;
        }
        
        //color
        if(splittedString[i].textColor.a >= splittedString[i].alpha)
        {
            splittedString[i].textColor.a -= 0.1;
        }
    }
}

void inputHandler::compareInput(string wantedWord)
{
    vector<string> duplicatesLetters;
    
    for(int i=0; i<splittedString.size(); i++)
    {
        size_t found = wantedWord.find(splittedString[i].letter);
        //cout << "try to find : " << splittedString[i].letter << endl;
        if (found!=string::npos)
        {
            cout << "found " << endl;
            
            if(std::find(duplicatesLetters.begin(), duplicatesLetters.end(), splittedString[i].letter) != duplicatesLetters.end())
            {
                splittedString[i].alpha = 0;
                cout << "duplicate entry " << endl;
            }
            else
            {
                splittedString[i].alpha = 255;
            }
            
            duplicatesLetters.push_back(splittedString[i].letter);
        }
        else
        {
            splittedString[i].alpha = 0;
            cout << "not found" << endl;
        }
    }
}



