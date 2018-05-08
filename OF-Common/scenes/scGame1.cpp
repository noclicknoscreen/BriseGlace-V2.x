//
//  scGame1.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame1.h"

void scGame1::setup(){  //load your scene 1 assets here...
    scScene::setup();
    ofLogNotice() << "Game 1 : Setup !";
    myTitle = "Game 1 : Mot caché";
};

void scGame1::update(float dt){ //update scene 1 here
};

void scGame1::draw(){ //draw scene 1 here
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::red);
    
    scScene::draw();            // Draw title
    myPlayerManager->draw();    // Draw players
    drawCenterText(myPlayerManager->getLastMessage(), 0, 50); // Draw last message

    ofPopStyle();
    
};

//scene notifications
void scGame1::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
};

//scene notifications
void scGame1::sceneWillDisappear( ofxScene * toScreen ){
}
