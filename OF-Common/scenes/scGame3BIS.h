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
//    scGame3BIS(playerManager &_manager) : scGame3(_manager){
//    };
    
    //--------------------------------------------------------------
    void sceneWillAppear( ofxScene * fromScreen ){
        
        scScene::sceneWillAppear(fromScreen);
        
        //now comes from enigma Singleton
        wantedWord = bigEnigmaManager().getCurrentEnigma()->getSolution();
        
        for(int i=0; i<wantedWord.size(); i++)
        {
            box = new specialBox();
            box->setup(texture, ofToString(wantedWord[i]), 40);
            box->create(world.world, ofVec3f(0, 600, 0), .5, 80, 80, 80);
            
            box->add();
            
            myCubes.push_back(box);
        }
        
        timer = ofGetElapsedTimef();
    };
    
    
    
    
    //--------------------------------------------------------------
    void update(float dt){
        
//        bigPlayerManager().update();
        
        camera.setPosition(ofVec3f(camPosX, camPosY, camPosZ));
        world.setGravity(ofVec3f(0,gravity, 0));
        
        world.update();
        
        for(int i=0; i<myCubes.size(); i++)
        {
            myCubes[i]->setActivationState(1);
        }
        
        //light
        spotLight.setOrientation( ofVec3f( 0, 45, 30) );
        spotLight.setPosition(ofGetWidth()-100, 100, 0);
        lightColor.setHue(0);
        spotLight.setDiffuseColor(lightColor);
        material.setSpecularColor(materialColor);
        
        //apply forces after 5 seconds
        if(ofGetElapsedTimef() - timer > 5)
        {
            //add the top of the physical box after 5 seconds ;)
            //top.add();
            
            amount = bigPlayerManager().getSumVolume();
            if(amount < 120 && amount > -120 )
                applyForceOnCubes(amount);
        }
        
        if(ofGetElapsedTimef() - timer > 10)
        {
            ofxSceneManager::instance()->goToScene(9);
        }
        
        
    };
};

#endif /* scGame3BIS_h */
