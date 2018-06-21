//
//  enigma.hpp
//  theBigGame
//
//  Created by Sébastien Albert on 10/05/2018.
//
//

#pragma once

#include "ofMain.h"
#include "enigmaHint.h"
#include "utils.h"

typedef enum {
    HINT1 = 0,
    HINT2,
    HINT3
} enigmaType;

const string tagTheme   = "theme";

//////////////////////////////////////////////////////////////////////////////////
class enigma{
    
public:

    bool load(string path);
    
    bool        getIsAvailable(enigmaType _type);
    
    string      getSolution(){return mSolution.getTitre();};
    ofImage     getImageSolution(){return mSolution.getImage();};
    
    string      getTitleRecompense(){return mRecompense.getTitre();};
    ofImage     getImageRecompense(){return mRecompense.getImage();};
    string      getLegende(){return mLegende;};
    string      getTheme(){return mTheme;};
    
    int         getNbHints(){return mHints.size();};
    
    ofImage     getImage(enigmaType _type);
    string      getTitre(enigmaType _type);
    
private:
    vector<enigmaHint>     mHints;
    enigmaHint             mRecompense;
    enigmaHint             mSolution;
    
    string  mLegende;
    string  mTheme;
    
    enigmaHint*  getHint(enigmaType _type);
    
};
