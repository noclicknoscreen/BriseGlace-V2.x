//
//  inputHandler.cpp
//  cubes
//
//  Created by Blindsp0t on 07/05/2018.
//
//

#include "inputHandler.h"
#include <algorithm>

void inputHandler::setup(ofPoint _inputTextPosition)
{
    font.load(globalFontName, globalFontSizeMedium);
    fontBig.load(globalFontName, globalFontSizeMedium + 15);
    
    revealMode = false;
    currentRevealCube = 0;
    currentRevealLetter = 0;
    
    nbCubesRotated = 0;
    
    mInputTextPosition = _inputTextPosition;
    
}

void inputHandler::reset(){
    duplicatesLetters.clear();
    splittedString.clear();
}

void inputHandler::getNewText(player _player)
{
    mReadyForNewText = false;
    
    ofLogNotice() << "got new input from user " << userId << " : " << _player.getLastMessageToCompare();
    
    text = utils::toUpperCase(_player.getLastMessageToCompare());
    
    ofPoint source;
    ofColor textColor;
    
    userId = _player.getNumber();
    textColor = _player.getColor();
    source = _player.getPosition();
    
    
    splittedString.clear();
    float cumulatedOffset = 0;
    
    for(int i=0; i<text.size(); i++)
    {
        letterElement oneSplitStr;
        oneSplitStr.letter = text.substr(i,1);
        
//        if(ofIsStringInString(ofToString(text[i]), bigEnigmaManager().getCurrentEnigma()-> getSolution()) > 0){
//            // We display the good letters in player color
//            oneSplitStr.textColor = textColor;
//        }else{
//            // The bad ones in gray
//            oneSplitStr.textColor = ofColor::gray;
//        }
        
        oneSplitStr.textColor = textColor;
        oneSplitStr.currentPos = source;
        oneSplitStr.destination = ofPoint(mInputTextPosition.x + 0.5 * (cumulatedOffset - font.getStringBoundingBox(text, 0, 0).getWidth()), mInputTextPosition.y);
        oneSplitStr.destination.y += ofRandom(0.0, 15.0); //add some random so the text isn't a line block
        
        oneSplitStr.alpha = 1.0;
        
        cumulatedOffset += font.getStringBoundingBox(oneSplitStr.letter, 0, 0).getWidth() + spaceBetweenLetters;
        
        splittedString.push_back(oneSplitStr);
    }
    
    
}

void inputHandler::draw()
{
    
    
    for(int i = 0; i < splittedString.size(); i++)
    {
        ofPushStyle();
        ofEnableAlphaBlending();
        
        ofPushMatrix();
        
        float scale = ofMap(splittedString[i].textColor.a, 1.0, 0.0, 1.0, 1.5);
//        ofLog() << "which alpha : " << splittedString[i].textColor.a << " : " << "scale : " << scale;
        
        ofTranslate(splittedString[i].currentPos);
        ofScale(scale, scale, scale);
        
        ofSetColor(splittedString[i].textColor);
        font.drawString(splittedString[i].letter, 0, 0);
        
        ofPopMatrix();
        ofPopStyle();
        
//        if(revealMode){
//            font.drawString(splittedString[i].letter, 0, 0);
//            
//        }else{
//            font.drawString(splittedString[i].letter, 0, 0);
//            
//            if(splittedString[i].alpha > 0){
//                font.drawString(splittedString[i].letter, splittedString[i].currentPos.x, splittedString[i].currentPos.y);
//                
//            }else{
//                fontBig.drawString(splittedString[i].letter, splittedString[i].currentPos.x, splittedString[i].currentPos.y);
//                
//            }
//        }
        

        
    }
    
}

void inputHandler::revealTirrets(cubeManager* cm)
{
    size_t found = wordToFind.find("-", 0);
    
    if(found!=string::npos)
    {
        cm->myCubes[found].rotateToLetter();
    }
    
}

int inputHandler::update(cubeManager* cm)
{
    
    bool lettersAreFading = false;
    bool returnValue = 0;
    
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
                cm->colorizeCube(index, splittedString[currentRevealCube].textColor);
                
                switch (bigEnigmaManager().getCurrentGameType()) {
                    case MOTUS:
                        cm->myCubes[index].rotateToLetter(); //rotate the corresponding cube
                        break;
                        
                    case IMAGE_GRID:
                        cm->myCubes[index].rotateToWhite(); //rotate the corresponding cube
                        break;
                        
                    default:
                        break;
                }
                
                //                cm->myCubes[index].rotateToLetter(); //rotate the corresponding cube
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
                ofLogNotice() << "reveal finished, ready to get another proposal from user ";
                revealMode = false;
                mReadyForNewText = true;
                
                ofNotifyEvent(readyForNewText, this);
                
                // On écarte les lettres/caractères introuvables (esapces, tirets) pour ne pas bloquer le jeu
                string easyWordToFind = wordToFind;
                easyWordToFind.erase (std::remove (easyWordToFind.begin(), easyWordToFind.end(), ' '), easyWordToFind.end());
                easyWordToFind.erase (std::remove (easyWordToFind.begin(), easyWordToFind.end(), '-'), easyWordToFind.end());
                
                if(nbCubesRotated == easyWordToFind.size())
                {
                    //WIN !
                    ofLogNotice() << "WIN = > return true, userId =  " << userId;
                    return userId;
                }
            }
        }
    }
    return 0;
}



void inputHandler::clearDuplicatesLettersHistory()
{
    duplicatesLetters.clear();
}

