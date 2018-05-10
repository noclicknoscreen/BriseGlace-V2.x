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
            path += "/MOTUS";
            break;
        case IMAGE_GRID:
            path += "/IMAGE_GRID";
            break;
        case BOGGLE:
            path += "/BOGGLE";
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
        for (int idxFolder=0; idxFolder < (int)dir.size(); idxFolder++) {
            ofFile oneFile = dir.getFile(idxFolder);
            if(oneFile.isDirectory()){
                ofLogNotice() << "Path n° " << ofToString(idxFolder) << "] " << dir.getPath(idxFolder);
            }
        }
    }
    
}

//void enigmaManager::draw(){
//    
//}
