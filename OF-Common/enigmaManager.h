//
//  enigmaManager.hpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 10/05/2018.
//
//

#pragma once

#include "ofMain.h"

#include "enigma.h"
#include "utils.h"

enum gameType {MOTUS = 1, IMAGE_GRID, BOGGLE};

//////////////////////////////////////////////////////////////////////////////////
class enigmaManager : public ofBaseApp{
    
public:
    //    void setup(ofEvent<player> _someoneSpoke);
    void setup();
    void update();
    //void draw();
    
    void pickNewEnigma(gameType _type);
    enigmaType  pickHintIndex();
    void        pushHintIndex();
    enigma* getCurrentEnigma(){return &mCurrentEnigma;};
    gameType getCurrentGameType(){return mCurrentGameType;};
    
private:
    enigmaType toEnigmaType(int _int);
    
private:
    enigma      mCurrentEnigma;
    gameType    mCurrentGameType;
    ofDirectory dir;
    
    int         nbHint;
    
    // pseudo-random string (half enigma answer, half random)
private:
    string    mPseudoString;
    
public:
    void      setPseudoString(int _length);
    char    pickPseudoLetter(int _idx);
    
public:
    static enigmaManager& get(){
        static enigmaManager myEnigmaManager;
        return myEnigmaManager;
    }
    
};

inline enigmaManager& bigEnigmaManager()
{
    return enigmaManager::get();
}


