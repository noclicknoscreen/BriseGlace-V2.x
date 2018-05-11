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

#include "enigmaHint.h"

typedef enum {
    HINT1 = 0,
    HINT2,
    HINT3,
    REWARD
} enigmaType;

//////////////////////////////////////////////////////////////////////////////////
class enigma{
    
public:
    
    enigma() : mReward("", ""){
    };

    bool load(string path);
    
    enigmaHint*  getHint(enigmaType _type);
    string      getDesc(){return mDesc;};
    string      getPath(){return mPath;};

private:
    string  mDesc;
    string  mPath;
    
    vector<enigmaHint>     mHints;
    enigmaHint             mReward;
    
};
