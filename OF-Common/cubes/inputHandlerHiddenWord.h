//
//  inputHandlerHiddenWord.hpp
//  theBigGame
//
//  Created by Sébastien Albert on 05/06/2018.
//
//

#pragma once

#include "inputHandler.h"

class inputHandlerHiddenWord : public inputHandler {
    
public:
    void setWordToFind(string _wantedWord);
    void getNewText(player _player);
    void compareInput(string wantedWord);
    
};
