#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bgCol = ofColor(200);
    roadCol = ofColor(0);
    
    ofBackground(bgCol);
    cc = CarController::getInstance(25,230, bgCol, roadCol);
    cc->setMaxVal(100, 150, 100, 40);
    //void CC::setMaxVal(float maxAcc, float maxVel, float force, float sd)
}

//--------------------------------------------------------------
void ofApp::update(){
    cc->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cc->draw();
    
    ofSetColor(255);
    string str = "Jammed #: "+ofToString(cc->getJammed(), 2);
    ofDrawBitmapString(str, 50, 50);
    str = "average vel: "+ofToString(cc->getAVel(), 2);
    ofDrawBitmapString(str, 50, 65);
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

