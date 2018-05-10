//
//  enigma.hpp
//  theBigGame
//
//  Created by Sébastien Albert on 10/05/2018.
//
//

#pragma once

#include "ofMain.h"
#include "ofxJson.h"

//////////////////////////////////////////////////////////////////////////////////
class enigma{
    
public:
    bool load(string path);

private:
    string  mDesc;
    
    vector<ofImage*>    hintImages;
    vector<string>      hintTexts;
    
    ofImage*            rewImage;
    string              rewText;
    
};
