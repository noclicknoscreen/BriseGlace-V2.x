//
//  enigmaManager.hpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 10/05/2018.
//
//

#pragma once

#include "ofMain.h"

enum gameType {MOTUS = 1, IMAGE_GRID, BOGGLE};

class enigmaManager : public ofBaseApp{
    
public:
    //    void setup(ofEvent<player> _someoneSpoke);
    void setup();
    void update();
    //void draw();
    
    string getEnigmaName();
    
    static enigmaManager& get(){
        static enigmaManager myEnigmaManager;
        return myEnigmaManager;
    }
    
};

inline enigmaManager& bigEnigmaManager()
{
    return enigmaManager::get();
}

