//
//  scGame3.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame3.h"

void scGame3::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Game 3 : Setup !";
    myTitle = "Game 3 : Boggle";
};


void scGame3::update(float dt){ //update scene 1 here
};

void scGame3::draw(){ //draw scene 1 here
    
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::blue);
    
    scScene::draw();            // Draw title
    myPlayerManager->draw();    // Draw players
    drawCenterText(myPlayerManager->getLastMessage(), 0, 50); // Draw last message
    
    ofPopStyle();
    
};

//scene notifications
void scGame3::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
};

//scene notifications
void scGame3::sceneWillDisappear( ofxScene * toScreen ){
}
