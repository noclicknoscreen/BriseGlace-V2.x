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
    display += "Solution : " + bigEnigmaManager().getCurrentEnigma()->getSolution() + "\n";
    display += "Legende : " + bigEnigmaManager().getCurrentEnigma()->getLegende() + "\n";
    
    ofDrawBitmapString(display, 0.1 * ofGetWidth(), 0.1 * ofGetHeight());
    
    ofImage myImage;
    
    // --- --- Reward --- --- //
    ofPushMatrix();
    ofTranslate(0.15 * ofGetWidth(), 0.3 * ofGetHeight());
    if(bigEnigmaManager().getCurrentEnigma()->getIsAvailable(REWARD)){
        myImage = bigEnigmaManager().getCurrentEnigma()->getImage(REWARD);
        
        myImage.draw(0,0, 0.25 * myImage.getWidth(), 0.25 * myImage.getHeight());
        ofDrawBitmapString(bigEnigmaManager().getCurrentEnigma()->getTitre(REWARD), 0, 25 +  0.25 * myImage.getHeight());
    }
    ofPopMatrix();
    
    // --- --- HINT 1 --- --- //
    ofPushMatrix();
    ofTranslate(0.15 * ofGetWidth(), 0.6 * ofGetHeight());
    if(bigEnigmaManager().getCurrentEnigma()->getIsAvailable(HINT1)){
        myImage = bigEnigmaManager().getCurrentEnigma()->getImage(HINT1);
        
        myImage.draw(0,0, 0.25 * myImage.getWidth(), 0.25 * myImage.getHeight());
        ofDrawBitmapString(bigEnigmaManager().getCurrentEnigma()->getTitre(HINT1), 0, 25 +  0.25 * myImage.getHeight());
    }
    ofPopMatrix();
    
    // --- --- HINT 2 --- --- //
    ofPushMatrix();
    ofTranslate(0.4 * ofGetWidth(), 0.6 * ofGetHeight());
    if(bigEnigmaManager().getCurrentEnigma()->getIsAvailable(HINT2)){
        myImage = bigEnigmaManager().getCurrentEnigma()->getImage(HINT2);
        
        myImage.draw(0,0, 0.25 * myImage.getWidth(), 0.25 * myImage.getHeight());
        ofDrawBitmapString(bigEnigmaManager().getCurrentEnigma()->getTitre(HINT2), 0, 25 +  0.25 * myImage.getHeight());
    }
    ofPopMatrix();
    
    
    // --- --- HINT 3 --- --- //
    ofPushMatrix();
    ofTranslate(0.65 * ofGetWidth(), 0.6 * ofGetHeight());
    if(bigEnigmaManager().getCurrentEnigma()->getIsAvailable(HINT3)){
        myImage = bigEnigmaManager().getCurrentEnigma()->getImage(HINT3);
        
        myImage.draw(0,0, 0.25 * myImage.getWidth(), 0.25 * myImage.getHeight());
        ofDrawBitmapString(bigEnigmaManager().getCurrentEnigma()->getTitre(HINT3), 0, 25 +  0.25 * myImage.getHeight());
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
