//
//  enigmaManager.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 10/05/2018.
//
//

#include "enigmaManager.h"

#define GLOBAL_PATH "../../../_enigmas"

void enigmaManager::setup(){
    ofLogNotice() << "Setup enigma manager as SINGLETON, Sick !";
}

void enigmaManager::update(){
    ofLogNotice() << "Update enigma manager !";
}

void enigmaManager::pickNewEnigma(gameType _type){
    
    
    string path = GLOBAL_PATH;
    
    switch (_type) {
        case MOTUS:
            path += "/motus";
            break;
        case IMAGE_GRID:
            path += "/memory";
            break;
        case BOGGLE:
            path += "/boggle";
            break;
        default:
            break;
    }
    
    // First, know all folder of one game type
    dir.listDir(path);
    dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    
    //allocate the vector to have as many ofImages as files
    if( dir.size() ){
        // Ok, we have some folders
        // you can now iterate through the files and load them into the ofImage vector
        int idxFolder = (int) ofRandom(dir.size());
        ofFile oneFile = dir.getFile(idxFolder);
        
        if(oneFile.isDirectory()){
            enigma newEnigma;
            if(newEnigma.load(oneFile.getAbsolutePath())){
                mCurrentEnigma = newEnigma;
            }
        }
        else
        {
            pickNewEnigma(_type);
        }
    }
    
}

enigmaType enigmaManager::pickHintIndex(){
    
    int rndIdx = (int)ofRandom(3);
    enigmaType toReturn;
    
    switch (rndIdx) {
        case 0:
            toReturn = HINT1;
            break;
        case 1:
            toReturn = HINT2;
            break;
        case 2:
            toReturn = HINT3;
            break;
        default:
            toReturn = HINT1;
            break;
    }
    
    return toReturn;
    
}

//void enigmaManager::draw(){
//    
//}
