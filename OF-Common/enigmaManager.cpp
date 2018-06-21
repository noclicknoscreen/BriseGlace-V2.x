//
//  enigmaManager.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 10/05/2018.
//
//

#include "enigmaManager.h"
#include <algorithm>
#include <string>

#define GLOBAL_PATH "../../../_enigmasNewForm/enigme"

void enigmaManager::setup(){
    ofLogNotice() << "Setup enigma manager as SINGLETON, Sick !";
    
    nbHint = 0;
}

void enigmaManager::update(){
    ofLogNotice() << "Update enigma manager !";
}

void enigmaManager::pickNewEnigma(gameType _gameType){
    
    
    string path = GLOBAL_PATH;
//    path += "/enigme";
//    switch (_gameType) {
//        case MOTUS:
//            path += "/motus";
//            break;
//        case IMAGE_GRID:
//            path += "/memory";
//            break;
//        case BOGGLE:
//            path += "/boggle";
//            break;
//        default:
//            break;
//    }
    
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
                
                nbHint = (int)ofRandom(mCurrentEnigma.getNbHints());

            }
        }
        else
        {
            pickNewEnigma(_gameType);
        }
    }
    
}

void enigmaManager::pushHintIndex(){
    // go to next hint
    nbHint++;
    // take care to not go too far
    if(nbHint >= mCurrentEnigma.getNbHints()){
        nbHint = 0;
    }
}

enigmaType enigmaManager::pickHintIndex(){
    return toEnigmaType(nbHint);
}

// PSEUDO STRING -----------------------------------------------
void enigmaManager::setPseudoString(int _length){
    
//    mPseudoString = ""; // Clear
//    mPseudoString.clear(); // Clear
    mPseudoString = utils::toUpperCase(mCurrentEnigma.getSolution());
    
    mPseudoString.erase(std::remove(mPseudoString.begin(), mPseudoString.end(), ' '), mPseudoString.end());
    
//    int savedSize = mPseudoString.size();
    if(_length > mPseudoString.size()){
        // On rajoute des lettre aléatoire
        for(int i = mPseudoString.size(); i < _length; i++){
            mPseudoString += utils::getRndLetter();
        }
    }else if(_length < mPseudoString.size()){
        mPseudoString.resize(_length);
    }
    
    // Manual shuffle
    // But don't touch to utf8 characters
    for(int idxLetter = 0; idxLetter < mPseudoString.size(); idxLetter++){
        
        int rndIdx = (int)ofRandom(0, mPseudoString.size());
        
        if(ofStringTimesInString("ÀÂÉÈÊÎÔÛÙŒÆÇ", ofToString(mPseudoString[rndIdx])) <= 0
           &&
           ofStringTimesInString("ÀÂÉÈÊÎÔÛÙŒÆÇ", ofToString(mPseudoString[idxLetter])) <= 0){
            
            std::swap(mPseudoString[idxLetter], mPseudoString[rndIdx]);
        }
    }
    ofLog() << "Pseudo chaine = " << mPseudoString << " longueur(" << ofToString(mPseudoString.size()) << ")";
    
}

char enigmaManager::pickPseudoLetter(int _idx){
    if(_idx >= 0 && _idx < mPseudoString.size()){
        // return a letter among the pseudo string
        return mPseudoString[_idx];
        
    }else{
        // else return anything random
        return utils::getRndLetter();
        
    }
}

enigmaType enigmaManager::toEnigmaType(int _int){
    
    enigmaType toReturn;
    
    switch (_int) {
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
