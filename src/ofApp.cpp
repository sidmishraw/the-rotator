//--------------------------------------------------------------
//
// CS235 - Rotate Pivot Manipulator Functions
//
//  This is implemented as a set of methods in the app class
//  (and not generalied as a seperate Manipulator class) 
//  as it is intended to be given as a test problem.
//
// Kevin M. Smith - SJSU - 3/17/2018
//
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(ofColor::black);
    rotator.setColor(ofColor::blueViolet);
    pivot.setColor(ofColor::lightGreen);
}

//  Set Pivot and Rotator Handle locations to center of image
//  and outside top edge.
//
void ofApp::setupHandles() {
    
    float w = picture.image.getWidth();
    float h = picture.image.getHeight();
    picture.pivot = ofVec3f(w / 2, h / 2);
    pivot.setPosition(picture.trans.x, picture.trans.y);
    rotator.setPosition(picture.trans.x, picture.trans.y - h / 2 - 20);
}


//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
// Draw picture and manipulator handles.
//
void ofApp::draw(){
    if (imageLoaded) {
        picture.draw();
        drawHandles();
    }
}

//-------------------------------------------------------------
// Draw Handles with a line connecting them
//
void ofApp::drawHandles() {
    ofDrawLine(pivot.trans, rotator.trans);
    pivot.draw();
    rotator.draw();
}

//--------------------------------------------------------------
// Delete image data 
//
void ofApp::doDelete() {
    if (imageLoaded) {
        picture.image.clear();
        imageLoaded = false;
    }
}


//--------------------------------------------------------------
//
void ofApp::keyPressed(int key){
    switch (key) {
        case 'F':
        case 'f':
            ofToggleFullscreen();
            break;
        case 'd':
            doDelete();
            break;
        case 'c':
      {
        // set image in a neutral postion, reset handles
        //
        picture.rot = 0;
        picture.trans = dropPoint;
        setupHandles();
        break;
      }
            
        case OF_KEY_DEL:
            doDelete();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
// mouseDragged - Do dragging of rotator and pivot handles.  
//
// if rotator dragged, we need to rotate image 
// if pivot dragged, update handle location but don't modify
// actual image pivot until mouse released.
//
using namespace std;
void ofApp::mouseDragged(int x, int y, int button){
    if(this->mode) {
        // pivot dragged
        this->pivot.setPosition(x, y); // update the pivot location but don't update the image
    } else {
        // rotator dragged
        this->rDragEndPoint = ofVec3f(x, y, 0);
        this->rotator.setPosition(this->rDragEndPoint.x, this->rDragEndPoint.y);
        
        this->pToR2 = this->rotator.trans - this->pivot.trans;
        
        auto angle = pToR2.angle(pToR1);
        auto dir = pToR1.getCrossed(pToR2).normalize();
        
        if(dir.z < 0) {
            // anti-clockwise rotation, -ve
            angle = -angle;
        }
        
        cout << "rot = " << angle << endl;
        
        this->picture.rot = angle;
    }
}

//--------------------------------------------------------------
//  mousePressed - check to see which handle we have pressed down
//  on. Save any state needed to do drag.
//
using namespace std;
void ofApp::mousePressed(int x, int y, int button){
    
    if (this->pivot.inside(x, y)) {
        this->mode = true;
        this->pDragStartPoint = ofVec3f(x, y, 0);
        cout << "Inside the pivot handler" << endl;
    } else if (this->rotator.inside(x, y)) {
        this->mode = false;
        this->rDragStartPoint = ofVec3f(x, y, 0);
        cout << "Inside the rotator handler" << endl;
    }
    
    this->pToR1 = this->rotator.trans - this->pivot.trans;
}

//--------------------------------------------------------------
// if pivot dragged, update pivot using Image::setPivot().
// you need to convert from screen space to image space since pivot is in image space.
// You need to translate image aftewards to the screen space location of the pivot
// 
void ofApp::mouseReleased(int x, int y, int button){
    
    if(this->mode) {
        // pivot handler moved
        this->pDragEndPoint = ofVec3f(x, y, 0);
        ofVec3f delta = this->pDragEndPoint - this->pDragStartPoint;
        this->pivot.setPosition(this->pDragEndPoint.x, this->pDragEndPoint.y);
        
        auto imageSpacePt = this->picture.screenToImageSpace(x, y);
        this->picture.setPivot(imageSpacePt);
        this->picture.trans = this->pivot.trans;
    } else {
        // rotator handler moved
        this->rDragEndPoint = ofVec3f(x, y, 0);
        ofVec3f delta = this->rDragEndPoint - this->rDragStartPoint;
        this->rotator.setPosition(this->rDragEndPoint.x, this->rDragEndPoint.y);
    }
    
    this->pToR1 = this->rotator.trans - this->pivot.trans;
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

//  Drop a single image into picture.  Only keeps one image at a time.
//  After images dropped. setup handles.
//
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
    if (picture.image.load(dragInfo.files[0]) == true)
      {
        // translate image to drop location
        //
        picture.trans = ofVec3f(dragInfo.position.x, dragInfo.position.y);
        dropPoint = picture.trans;
        imageLoaded = true;
        setupHandles();
        
      }
    else {
        cout << "Can't load image: " << dragInfo.files[0] << endl;
    }
}


