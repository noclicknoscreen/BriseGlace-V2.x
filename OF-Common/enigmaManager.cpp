//
//  enigmaManager.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 10/05/2018.
//
//

#include "enigmaManager.h"

void enigmaManager::setup(){
    ofLogNotice() << "Setup enigma manager as SINGLETON, Sick !";
}
void enigmaManager::update(){
    ofLogNotice() << "Update enigma manager !";
}

string enigmaManager::getEnigmaName(){
    return "C'est moi!";
}
//void enigmaManager::draw(){
//    
//}
