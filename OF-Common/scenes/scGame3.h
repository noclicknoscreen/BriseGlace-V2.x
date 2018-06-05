//
//  MyScene1.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 11/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "scScene.h"
#include "ofxGui.h"
#include "ofxBullet.h"


#define START_FORCE_FACTOR 300//250//100
#define PLAY_FORCE_FACTOR  7

class specialBox : public ofxBulletBox
{
    string letter;
    ofImage texture;
    ofTrueTypeFont font;
    
    ofMaterial materialForFaceColor;
    
public:
    void customDraw(ofColor _winnerColor=ofColor::white)
    {
        transformGL();
        
        ofPushMatrix();
        ofRotate(-90, 1, 0, 0);
        
            ofVec3f size = getSize();
            
            //apply texture
            ofEnableNormalizedTexCoords();
            texture.bind();
            
            //3d box
            ofSetColor(255);
            
            ofFill();
            ofDrawBox(0, 0, 0, size.x, size.y, size.z);
        
            texture.unbind();
            ofDisableNormalizedTexCoords();
            
            
            //letter
            float textHeight, textWidth;
            textWidth = font.getStringBoundingBox(letter, 0, 0).getWidth();
            textHeight = font.getStringBoundingBox(letter, 0, 0).getHeight();
            
        
        
        if(_winnerColor != ofColor::white)
        {
            ofPushMatrix();

            materialForFaceColor.setAmbientColor(_winnerColor);
            materialForFaceColor.setDiffuseColor(ofColor(_winnerColor, 140));
            
            materialForFaceColor.begin();
            
            ofTranslate(0,0, size.z/2 + 1);
            ofDrawRectangle(-size.x/2, -size.y/2, size.x, size.y);
            
            materialForFaceColor.end();
            ofSetColor(255);
            
            ofPopMatrix();
        }

        
        ofSetColor(0);
        ofPushMatrix();
                ofRotate(180, 0, 0, 1);
                ofRotate(180, 0, 1, 0);
                ofRotate(180, 1, 0, 0);
        
                ofTranslate(-textWidth/2.0,  -textHeight/2, float(size.z/2 +2));
                
                ofDisableLighting();
                font.drawString(letter, 0, 0);
                ofEnableLighting();
            ofPopMatrix();

        ofPopMatrix();
        
        //restore gl state
        restoreTransformGL();
        
        
        
        
    }
    
    void setLetter(string _letter)
    {
        letter = _letter;
    }
    
    void setTexture(ofImage _texture)
    {
        texture = _texture;
    }
    
    void setup(ofImage _image, string _letter, float _size)
    {
        setTexture(_image);
        setLetter(_letter);
        font.load(globalFontName, 34);
        
        //setSize(_size);
    }
};


class scGame3 : public scScene{

public:

    
    void setup();
    void update(float dt);
	void draw();
    void setupGui();
    void setupPhysics();
    void setupLight();
    
    void someoneSpoke(player & _player);
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    void timerEnd();
    void timerSignWinEnd();
    void timerSignHintEnd();
    
    void keyPressed(int key);
    void exit();
    
    //physics
    ofxBulletWorldRigid			world;
    ofxBulletBox				ground, rightFace, leftFace, bottom, front, top;
    specialBox*                 box;
    
    void applyForceOnCubes(ofVec3f force, ofPoint _frcPos);
    float amount;
    
    //camera
    //ofEasyCam					camera;
    ofCamera					camera;
    
    //the word to find
    string wantedWord;
    
    //texture
    ofImage texture;

    //the cubes
    vector<specialBox*>          myCubes;
    
    //background image
//    ofImage background;
    
    //parameters
    ofxPanel                     gui;
    bool                         bDrawGui;
    ofParameter<float>           camPosX, camPosY, camPosZ, gravity, angularDamping, damping, friction;
    ofParameter<float>           volumeBorneMin, volumeBorneMax;
    ofParameter<float> forceMicro2_multiplier;
    ofParameter<ofVec3f>         forceAmount;
    ofParameter<float>           zLight;
    
    //lumiere
    ofLight spotLight;
    ofColor lightColor;
    ofColor materialColor;
    ofMaterial material;
    
    //timer
    float timer;
    
    //winner color (for game3BIS ;)
protected:
    bool colorizeCubes;
    
};

