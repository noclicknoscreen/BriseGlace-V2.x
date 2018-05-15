//
//  scGame3BIS.h
//  theBigGame
//
//  Created by Blindsp0t on 15/05/2018.
//
//

#ifndef scGame3BIS_h
#define scGame3BIS_h

#include "scGame3.h"

class scGame3BIS : public scGame3
{
public:
    scGame3BIS(playerManager &_manager) : scGame3(_manager){
    };
    
    
    void sceneWillAppear( ofxScene * fromScreen ){
        
        scScene::sceneWillAppear(fromScreen);
        
        //now comes from enigma Singleton
        bigEnigmaManager().pickNewEnigma(MOTUS);
        wantedWord = bigEnigmaManager().getCurrentEnigma()->getSolution();
        cout << "setting wantedWord to : " << wantedWord << endl;
        
        for(int i=0; i<wantedWord.size(); i++)
        {
            box = new specialBox();
            box->setup(texture, ofToString(wantedWord[i]), 40);
            box->create(world.world, ofVec3f(0, 600, 0), .5, 80, 80, 80);
            
            box->add();
            //box->applyForce(START_FORCE_FACTOR*ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)), box->getPosition());
            
            myCubes.push_back(box);
        }
        
        timer = ofGetElapsedTimef();
    };
};

#endif /* scGame3BIS_h */
