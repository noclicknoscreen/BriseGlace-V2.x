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

    bool load(string path);
    
    ofImage     getImage(enigmaType _type);
    ofImage     getCurrentImage(){getImage(enigmaType(currentImageId)); currentImageId++;};
    string      getTitre(enigmaType _type);
    bool        getIsAvailable(enigmaType _type);
    
    string       getSolution(){return mSolution;};
    string       getLegende(){return mLegende;};
    
private:
    string  mLegende;
    string  mSolution;
    
    vector<enigmaHint>     mHints;
    enigmaHint             mReward;
    
    enigmaHint*  getHint(enigmaType _type);
    
    int currentImageId=0;
    
    
};
