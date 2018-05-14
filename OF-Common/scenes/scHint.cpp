//
//  scHint.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scHint.h"

void scHint::setup(){  //load your scene 1 assets here...
    
    scScene::setup();
    ofLogNotice() << "Indice : Setup !";
    myTitle = "Ecran d'indices";
    
    
   

};


void scHint::update(float dt){ //update scene 1 here
    
    myIndice.update();
    
    if(ofGetElapsedTimef() - timer > 5)
        myIndice.setRevealMode();
    
};

void scHint::draw(){ //draw scene 1 here
    
    ofEnableDepthTest();
    myIndice.draw();
    
};

//scene notifications
void scHint::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    
    ofEnableDepthTest();
    ofEnableLighting();
     myIndice.setup();
    
    timer = ofGetElapsedTimef();
};

//scene notifications
void scHint::sceneWillDisappear( ofxScene * toScreen ){
}




