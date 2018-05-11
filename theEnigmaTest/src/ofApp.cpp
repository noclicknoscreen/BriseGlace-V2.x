#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Load the next enigma
    bigEnigmaManager().pickNewEnigma(MOTUS);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    string display;
    
    display += "Current Enigma : \n";
    display += bigEnigmaManager().getCurrentEnigma()->getDesc() + "\n";
    display += bigEnigmaManager().getCurrentEnigma()->getPath();
    
    ofDrawBitmapString(display, 0.1 * ofGetWidth(), 0.1 * ofGetHeight());
    
    enigmaHint myReward = *bigEnigmaManager().getCurrentEnigma()->getHint(REWARD);
    enigmaHint myHint1 = *bigEnigmaManager().getCurrentEnigma()->getHint(HINT1);
    enigmaHint myHint2 = *bigEnigmaManager().getCurrentEnigma()->getHint(HINT2);
    enigmaHint myHint3 = *bigEnigmaManager().getCurrentEnigma()->getHint(HINT3);
    ofImage myImage;
    
    // --- --- Reward --- --- //
    ofPushMatrix();
    ofTranslate(0.15 * ofGetWidth(), 0.3 * ofGetHeight());
    if(myReward.isAvailable()){
        myImage = myReward.getImage();
        
        myImage.draw(0,0, 0.25 * myImage.getWidth(), 0.25 * myImage.getHeight());
        ofDrawBitmapString(myReward.getDescription(), 0, 25 +  0.25 * myImage.getHeight());
    }
    ofPopMatrix();
    
    // --- --- HINT 1 --- --- //
    ofPushMatrix();
    ofTranslate(0.15 * ofGetWidth(), 0.6 * ofGetHeight());
    if(myHint1.isAvailable()){
        myImage = myHint1.getImage();
        
        myImage.draw(0,0, 0.25 * myImage.getWidth(), 0.25 * myImage.getHeight());
        ofDrawBitmapString(myHint1.getDescription(), 0, 25 +  0.25 * myImage.getHeight());
    }
    ofPopMatrix();
    
    // --- --- HINT 2 --- --- //
    ofPushMatrix();
    ofTranslate(0.4 * ofGetWidth(), 0.6 * ofGetHeight());
    if(myHint2.isAvailable()){
        myImage = myHint2.getImage();
        
        myImage.draw(0,0, 0.25 * myImage.getWidth(), 0.25 * myImage.getHeight());
        ofDrawBitmapString(myHint2.getDescription(), 0, 25 +  0.25 * myImage.getHeight());
    }
    ofPopMatrix();
    
    
    // --- --- HINT 3 --- --- //
    ofPushMatrix();
    ofTranslate(0.65 * ofGetWidth(), 0.6 * ofGetHeight());
    if(myHint3.isAvailable()){
        myImage = myHint3.getImage();
        
        myImage.draw(0,0, 0.25 * myImage.getWidth(), 0.25 * myImage.getHeight());
        ofDrawBitmapString(myHint3.getDescription(), 0, 25 +  0.25 * myImage.getHeight());
    }
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        // Load the next enigma
        bigEnigmaManager().pickNewEnigma(MOTUS);
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
