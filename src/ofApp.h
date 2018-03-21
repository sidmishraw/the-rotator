//--------------------------------------------------------------
//
// CS235 - Rotate Pivot Manipulator
//
// Kevin M. Smith - SJSU - 3/17/2018
//
#pragma once

#include "ofMain.h"
#include "Image.h"
#include "Handle.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void doDelete();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void setupHandles();
    void drawHandles();
    
    // only one picture loaded at a time.
    //
    Image picture;
    
    // handles for pivot point and rotator
    //
    ManipHandle pivot, rotator;
    
    // internal state variables
    //
    bool imageLoaded = false;
    ofVec3f dropPoint;              // save place where image is dropped
    
    // put your state variables here....
    //
    bool mode; // flag for mode handler
    ofVec3f pDragStartPoint; // the drag start point for pivot handler
    ofVec3f rDragStartPoint; // the drag start point for rotator handler
    ofVec3f pDragEndPoint; // drag end point for pivot handler
    ofVec3f rDragEndPoint; // the drag end point for the rotator handler
    
    ofVec3f pToR1; // vector from pivot to rotator - initial
    ofVec3f pToR2; // vector from pivot to rotator - final
};
