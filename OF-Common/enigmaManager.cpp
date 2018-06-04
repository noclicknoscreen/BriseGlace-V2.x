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

void enigmaManager::pickNewEnigma(gameType _gameType){
    
    
    string path = GLOBAL_PATH;
    
    switch (_gameType) {
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
                mCurrentGameType = _gameType;
            }
        }
        else
        {
            pickNewEnigma(_gameType);
        }
    }
    
}

//void enigmaManager::draw(){
//    
//}
