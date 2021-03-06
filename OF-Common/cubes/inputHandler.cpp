//
//  inputHandler.cpp
//  cubes
//
//  Created by Blindsp0t on 07/05/2018.
//
//

#include "inputHandler.h"
#include <algorithm>

void inputHandler::setup(ofPoint _inputTextPosition, float _maxWidth, float _lineHeight)
{
    font.load(globalFontName, globalFontSizeMedium);
    fontBig.load(globalFontName, globalFontSizeMedium + 15);
    
    revealMode = false;
    currentRevealCube = 0;
    currentRevealLetter = 0;
    
    nbCubesRotated = 0;
    
    mInputTextPosition = _inputTextPosition;
    mMaxWidth = _maxWidth;
    mLineHeight = _lineHeight;
    
}

void inputHandler::resetInputs(){
//    duplicatesLetters.clear();
    splittedString.clear();
}

void inputHandler::resetDuplicates(){
    duplicatesLetters.clear();
//    splittedString.clear();
}

void inputHandler::getNewText(player _player)
{
    mReadyForNewText = false;
    
    ofLogNotice() << "got new input from user " << userId << " : " << _player.getLastMessage();
    
    text = utils::toUpperCase(_player.getLastMessage());
    
    ofPoint source;
    ofColor textColor;
    
    userId = _player.getNumber();
    textColor = _player.getColor();
    source = _player.getPosition();
    
    
    splittedString.clear();
    float cumulatedOffset = 0;
    
    vector<string> splittedText = ofSplitString(text, " ");
    
    float textWidth = 0;
    int   idxLine = 0;
    int   nbLines = 0;
    string strTheLine = "";
    
    ofLogNotice() << "Input string from position: " << source << " to position: " << mInputTextPosition;
    
    float totalWidth = text.size() * spaceBetweenLetters + font.getStringBoundingBox(text, 0, 0).getWidth();
    nbLines = (int)totalWidth / mMaxWidth;
    
    for (int idxTxt = 0; idxTxt < splittedText.size(); idxTxt++) {
        
        textWidth += splittedText[idxTxt].size() * spaceBetweenLetters + font.getStringBoundingBox(splittedText[idxTxt], 0, 0).getWidth();
        // Don't draw, accumulate strings
        strTheLine += splittedText[idxTxt] + " ";
        
        if(textWidth > mMaxWidth || (idxTxt == splittedText.size()-1)){
            
            // Draw the line
            for(int i=0; i<strTheLine.size(); i++)
            {
                letterElement oneSplitStr;
                oneSplitStr.letter = strTheLine.substr(i,1);
                
                oneSplitStr.textColor = textColor;
                oneSplitStr.currentPos = source;
                oneSplitStr.destination.x = mInputTextPosition.x + 0.5 * cumulatedOffset - font.getStringBoundingBox(strTheLine, 0, 0).getWidth();
                oneSplitStr.destination.y = mInputTextPosition.y + mLineHeight*(0.5*nbLines - idxLine) + ofRandom(0.0, 15.0); //add some random so the text isn't a line block
                
                ofLogNotice() << "The letter " << oneSplitStr.letter << " goes to position: " << oneSplitStr.destination << " Line = " << idxLine << " x " << mLineHeight;
                
                oneSplitStr.alpha = 1.0;
                
                cumulatedOffset += font.getStringBoundingBox(oneSplitStr.letter, 0, 0).getWidth() + spaceBetweenLetters;
                
                splittedString.push_back(oneSplitStr);
            }
            
            idxLine++;
            textWidth = 0;
            cumulatedOffset = 0;
            strTheLine = "";
            
        }

    }
    
}

void inputHandler::draw()
{

    for(int i = 0; i < splittedString.size(); i++)
    {
        ofPushStyle();
        
        ofDisableLighting();
        ofEnableAlphaBlending();
        
        ofPushMatrix();
        
        float scale = ofMap(splittedString[i].textColor.a, 1.0, 0.0, 1.0, 1.5);
        
        ofTranslate(splittedString[i].currentPos);
        ofScale(scale, scale, scale);
        
        ofSetColor(splittedString[i].textColor);
        font.drawString(splittedString[i].letter, 0, 0);
        
        ofPopMatrix();
        ofPopStyle();
        
    }
    
}

void inputHandler::revealTirrets(cubeManager* cm)
{
    size_t found;
    
    found = wordToFind.find("-", 0);
    if(found!=string::npos)
    {
        cm->myCubes[found].rotateToLetter();
    }

    found = wordToFind.find("'", 0);
    if(found!=string::npos)
    {
        cm->myCubes[found].rotateToLetter();
    }
    
}

int inputHandler::update(cubeManager* cm, float _alphaDecay)
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
            splittedString[i].textColor.a -= _alphaDecay;
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
                
                ofLogNotice() << "Rotating a new cube, pos:" << ofToString(currentRevealCube) << " ,letter:" << splittedString[currentRevealCube].letter;
                ofLogNotice() << "nb cubes rotated :" << ofToString(nbCubesRotated) << " ,wordToFind size:" << ofToString(wordToFind.size());
                
                
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
                ofLogNotice() << "word to find is : " << easyWordToFind;
                
                easyWordToFind.erase (std::remove (easyWordToFind.begin(), easyWordToFind.end(), '-'), easyWordToFind.end());
                ofLogNotice() << "word to find is : " << easyWordToFind;
                
                if(nbCubesRotated >= easyWordToFind.size())
                {
                    //WIN !
                    ofLogNotice() << "WIN ( " << ofToString(nbCubesRotated) << ">= " << ofToString(easyWordToFind.size()) << ") ====> return userId =  " << userId;
                    return userId;
                }else{
                    ofLogNotice() << "NOT WIN ( " << ofToString(nbCubesRotated) << "< " << ofToString(easyWordToFind.size()) << ")";
                }
                
            }
        }
    }
    return 0;
}

