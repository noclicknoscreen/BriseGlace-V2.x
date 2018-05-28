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
        wantedWord = utils::toUpperCase(bigEnigmaManager().getCurrentEnigma()->getSolution());
        
        for(int i=0; i<myCubes.size(); i++)
        {
            myCubes[i]->remove();
        }
        myCubes.clear();
        
        for(int i=0; i<wantedWord.size(); i++)
        {
            box = new specialBox();
//            box->setup(texture, ofToString(wantedWord[wantedWord.size()-(i+1)]), 40);
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
        
        //display result for 10 seconds and go to winner screen
        if(ofGetElapsedTimef() - timer > 5)
        {
            ofxSceneManager::instance()->goToScene(9);
        }
        

        //materialColor = winnerColor;
        
    };
    
    
    //--------------------------------------------------------------
    void draw(){

        ofEnableAntiAliasing();
        ofEnableSmoothing();
        ofEnableAlphaBlending();
        ofEnableDepthTest();
        
        ofSetBackgroundColor(255);
        
        ofEnableLighting();
        spotLight.enable();
        
        material.setAmbientColor(materialColor);
        material.setDiffuseColor(materialColor);
        
        camera.begin();
        
#if defined DRAW_DEBUG
        ofSetColor(100, 100, 100);
        ofNoFill();
        ground.draw();
        rightFace.draw();
        leftFace.draw();
        bottom.draw();
        ofFill();
        
        spotLight.draw();
#endif
        
        material.begin();
        for(int i=0; i<myCubes.size(); i++)
        {
            myCubes[i]->customDraw(winnerColor);
        }
        material.end();
        ofDisableLighting();
        
#if defined DRAW_DEBUG
        world.drawDebug();
#endif
        
        camera.end();
        
        
        ofDisableDepthTest();
        
        if(drawGui)
            gui.draw();
        
        //ofDrawBitmapString("volume amount : " + ofToString(amount) + "NumberOfPlayers" + ofToString(bigPlayerManager().getNumberOfPlayers()), 100, 100);
        
        // Draw title
        scScene::drawTitle("Mot brassé");
        //scScene::drawSubTitle("Parlez dans l'oreille pour retourner les cubes");
        
        // Draw players
        bigPlayerManager().draw();
        
    };
    
    
    
};

#endif /* scGame3BIS_h */
