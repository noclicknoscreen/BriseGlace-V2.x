#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    gui.setup();
    //gui.add
    gui.add(lightPosX.set("lightPosX", 850, -1000, 1000));
    gui.add(lightPosY.set("lightPosY", 120, -1000, 1000));
    gui.add(lightPosZ.set("lightPosZ", 0, -100, 100));
    gui.add(cubesRotationSpeed.set("cubesRotationSpeed", 5, 0.1, 20));
    
    //cubes
    myCubeManager.setup();
    
    //inputs
    myInputManager.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    myCubeManager.update(ofPoint(lightPosX, lightPosY, lightPosZ), cubesRotationSpeed);
    myInputManager.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    myCubeManager.draw();
    myInputManager.draw();
    
    ofDisableLighting();
    ofDisableDepthTest();
    ofSetColor(255);
    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='l')
        myCubeManager.rotateToLetter(0);
    if(key=='w')
        myCubeManager.rotateToWood(0);
    if(key=='W')
        myCubeManager.rotateToWhite(0);
    
    if(key==' ')
        myCubeManager.getWord("antoine");
    
    if(key=='p')
    {
        myInputManager.getNewText(1, "choucroute");
    }
    
    if(key=='c')
    {
        myInputManager.compareInput("antoine");
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
