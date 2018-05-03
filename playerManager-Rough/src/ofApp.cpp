#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackgroundGradient(ofColor::lightGrey, ofColor::black);
    myPlayerManager.setup();
    
    
    ofTrueTypeFont::setGlobalDpi(72);
    
    myFont.load("Folktale.ttf", 28, true, true);
    myFont.setLineHeight(18.0f);
    myFont.setLetterSpacing(1.037);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    myPlayerManager.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    myPlayerManager.draw();
    
    ofPushMatrix();
    
        string message = ofToString(myPlayerManager.getLastNumber()) + " : " + myPlayerManager.getLastMessage();
        ofRectangle bounds = myFont.getStringBoundingBox(message, 0, 0);
        
        ofTranslate(0.5 * (ofGetWidth() - bounds.width), 0.5 * (ofGetHeight() - bounds.height));
        myFont.drawString(message, 0, 0);
    
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
