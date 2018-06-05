//
//  inputHandlerMemory.hpp
//  theBigGame
//
//  Created by Sébastien Albert on 05/06/2018.
//
//

#pragma once

#include "ofMain.h"

#include "inputHandler.h"

class inputHandlerMemory : public inputHandler {
    
private:
    string mMysteryRandomString;   // This is the string defined at startup with the random picke letters
    
public:
    void setMysteryString(string _mysteryString){mMysteryRandomString = _mysteryString;};
    void getNewText(player _player);
    void compareInput(string wantedWord);
    
};
