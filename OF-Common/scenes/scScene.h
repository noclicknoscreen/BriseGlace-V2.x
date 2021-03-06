//
//  scScene.hpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 07/05/2018.
//
//

#pragma once

#include "ofxSceneManager.h"

#include "ofMain.h"
#include "ofxScene.h"
#include "ofxAnimatableFloat.h"
#include "ofxTextSuite.h"

#include "ofEvents.h"
#include "playerManager.h"
#include "enigmaManager.h"

#include "utils.h"

enum Scenes{SELECT_GAME = 1, GAME1, GAME2, GAME3, GAME3_BIS, HINT, VICTORY, PARTNERS};

class scScene : public ofxScene, ofBaseApp {
    
    
public:
    void setup();
    void update(float dt);
    
    void drawTitle(string _text, ofColor _color = ofColor::black, ofPoint _correc = ofPoint(0,0));
    void drawSubTitle(string _text, ofColor _color = ofColor::black, ofPoint _correc = ofPoint(0,0));
    
    void drawFullCenterLine1(string _text, ofColor _color = ofColor::black, ofPoint _correc = ofPoint(0,0));
    void drawFullCenterLine2(string _text, ofColor _color = ofColor::black, ofPoint _correc = ofPoint(0,0));
    void drawFullCenterLine3(string _text, ofColor _color = ofColor::black, ofPoint _correc = ofPoint(0,0));
    
    void drawSpokenWord(string _text, ofColor _color = ofColor::black, ofPoint _correc = ofPoint(0,0));
    
//    scScene(playerManager &_manager);
    
    void someoneSpoke(player & _player);
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
    ///////////// MEMBERS /////////////////////
private:
    ofxTextBlock myTextTitle;
    ofxTextBlock myTextSubTitle;
    ofxTextBlock myTextSpokenWord;

};

