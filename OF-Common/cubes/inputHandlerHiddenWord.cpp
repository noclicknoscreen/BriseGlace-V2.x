//
//  inputHandlerHiddenWord.cpp
//  theBigGame
//
//  Created by Sébastien Albert on 05/06/2018.
//
//

#include "inputHandlerHiddenWord.h"


void inputHandlerHiddenWord::setWordToFind(string _wantedWord){
    
    //supression des caractères non valide (espace, tirets, accents, etc.)
    _wantedWord.erase (std::remove (_wantedWord.begin(), _wantedWord.end(), ' '), _wantedWord.end());
    //    _wantedWord.erase (std::remove (_wantedWord.begin(), _wantedWord.end(), '-'), _wantedWord.end());
    
    wordToFind = _wantedWord;
    
};

void inputHandlerHiddenWord::getNewText(player _player)
{
    
    inputHandler::getNewText(_player);
    
    //GET THE WANTED WORD FROM THE ENIGMA SINGLETON
    compareInput(wordToFind);
    
    setRevealMode();
    
}

void inputHandlerHiddenWord::compareInput(string wantedWord)
{
    //supression des caractères non valide (espace, tirets, accents, etc.)
    wantedWord.erase (std::remove (wantedWord.begin(), wantedWord.end(), ' '), wantedWord.end());
    
    for(int i=0; i<splittedString.size(); i++)
    {
        size_t found = wantedWord.find(splittedString[i].letter, 0);
        ofLogNotice() << "compare this letter : " << splittedString[i].letter;
        if(found==string::npos)
        {
            splittedString[i].alpha = 0;
            ofLogNotice() << "not found => alpha=0";
        }
        
        while (found!=string::npos)
        {
            
            if(std::find(duplicatesLetters.begin(), duplicatesLetters.end(), splittedString[i].letter) != duplicatesLetters.end())
            {
                splittedString[i].alpha = 0;
                ofLogNotice() << "found DUPLICATE => alpha=0";
            }
            else
            {
                splittedString[i].alpha = 1.0;
                splittedString[i].correspondingCubes.push_back((int)found);
                ofLogNotice() << "found correspondance => alpha=1.0";
                
            }
            found = wantedWord.find(splittedString[i].letter, found+1);
        }
        ofLogNotice() << "add to duplicates list ";
        duplicatesLetters.push_back(splittedString[i].letter);
        
    }
    
}
