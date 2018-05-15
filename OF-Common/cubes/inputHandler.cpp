//
//  inputHandler.cpp
//  cubes
//
//  Created by Blindsp0t on 07/05/2018.
//
//

#include "inputHandler.h"
#include <algorithm>

void inputHandler::setup()
{
    font.load("Avenir.ttc", 24);
    
    revealMode = false;
    currentRevealCube = 0;
    currentRevealLetter = 0;
    
    nbCubesRotated = 0;
}

void inputHandler::getNewText(player _player)
{
    readyForNewText = false;
    
    cout << "got new input from user " << userId << " : " << _player.getLastMessageToCompare() << endl;
    
    //TODO A REMETTRE !
    text = utils::toUpperCase(_player.getLastMessageToCompare());

    ofPoint source;
    ofColor textColor;
    
    lastPlayerToTalk = & _player;
    userId = _player.getNumber();
    textColor = _player.getColor();
    source = _player.getPositionHistogram();
    
    
    splittedString.clear();
    float cumulatedOffset = 0;
    
    for(int i=0; i<text.size(); i++)
    {
        letterElement elt;
        elt.letter = text.substr(i,1);//ofToString(text[i]);
        elt.textColor = textColor;
        
        elt.sourcePos = source;
        elt.currentPos = source;
        elt.destination = ofPoint(cumulatedOffset + ofGetWidth()/2 - font.getStringBoundingBox(text, 0, 0).getWidth(), inputTextYPosition);
        
        elt.alpha = 1.0;
        
        cumulatedOffset += font.getStringBoundingBox(elt.letter, 0, 0).getWidth() + spaceBetweenLetters;
        
        splittedString.push_back(elt);
    }
    
    
    //GET THE WANTED WORD FROM THE ENIGMA SINGLETON
    compareInput(wordToFind);
    setRevealMode();
    
}

void inputHandler::draw()
{
        for(int i=0; i<splittedString.size(); i++)
        {
            ofSetColor(splittedString[i].textColor);
            font.drawString(splittedString[i].letter, splittedString[i].currentPos.x, splittedString[i].currentPos.y);
        }
}

void inputHandler::update(cubeManager* cm)
{
    
    bool lettersAreFading = false;
    
    for(int i=0; i<splittedString.size(); i++)
    {
        //movement to center
        if(splittedString[i].currentPos != splittedString[i].destination)
        {
            splittedString[i].currentPos += (splittedString[i].destination - splittedString[i].currentPos)/movementSmoothingValue;
        }
        
        //color
        if(splittedString[i].textColor.a > splittedString[i].alpha)
        {
            lettersAreFading = true;
            splittedString[i].textColor.a -= 0.01;
        }
        
    }
    
    //reveal corresponding cubes
    if(revealMode && !lettersAreFading)
    {
        bool next = true;
        bool somebodyRotating = false;
        
        //iterate through letters forming the user proposal
        if(splittedString[currentRevealCube].correspondingCubes.size() > 0)
        {
            int index = splittedString[currentRevealCube].correspondingCubes[currentRevealLetter];
            
                //check if a cube is already rotating
                for(int c=0; c<cm->myCubes.size(); c++)
                {
                    if(cm->myCubes[c].isRotating)
                        somebodyRotating = true;        
                }
            
            if(somebodyRotating)
            {
                next = false; //wait
            }
            else
            {
                cm->colorizeCube(index, lastPlayerToTalk->getColor());
                cm->myCubes[index].rotateToLetter(); //rotate the corresponding cube
                nbCubesRotated ++;                   //count one letter found more
                splittedString[currentRevealCube].alpha = 0;
            }
        }
            if(next)
            {
                if(currentRevealLetter+1 < splittedString[currentRevealCube].correspondingCubes.size())
                {
                    currentRevealLetter++;
                }
                else if(currentRevealCube+1 < splittedString.size())
                {
                    currentRevealCube++;
                    currentRevealLetter = 0;
                }
                else
                {
                    cout << "reveal finished, ready to get another proposal from user " << endl;
                    revealMode = false;
                    readyForNewText = true;
                    if(nbCubesRotated == wordToFind.size())
                    {
                        ofxSceneManager::instance()->goToScene(9);
                    }
                    
                }
            }
    }
}

void inputHandler::compareInput(string wantedWord)
{
    //supression des accents :
    wantedWord.erase (std::remove (wantedWord.begin(), wantedWord.end(), ' '), wantedWord.end());
    
    for(int i=0; i<splittedString.size(); i++)
    {
        size_t found = wantedWord.find(splittedString[i].letter, 0);
        cout << "compare this letter : " << splittedString[i].letter << endl;
        if(found==string::npos)
        {
            splittedString[i].alpha = 0;
            cout << "not found => alpha=0" << endl;
        }
        
        while (found!=string::npos)
        {
            
            if(std::find(duplicatesLetters.begin(), duplicatesLetters.end(), splittedString[i].letter) != duplicatesLetters.end())
            {
                splittedString[i].alpha = 0;
                cout << "found DUPLICATE => alpha=0" << endl;
            }
            else
            {
                splittedString[i].alpha = 1.0;
                splittedString[i].correspondingCubes.push_back((int)found);
                cout << "found correspondance => alpha=1.0" << endl;
                
            }
            found = wantedWord.find(splittedString[i].letter, found+1);
        }
        cout << "add to duplicates list " << endl;
        duplicatesLetters.push_back(splittedString[i].letter);

    }

}


void inputHandler::clearDuplicatesLettersHistory()
{
    duplicatesLetters.clear();
}

