
//--------------------------------------------------------------
//
//  CS235 - User Interface Design - Kevin M. Smith
//
//  Class wrapper for an image
// 
//  Simple class wrapper to store an ofImage with
//  tranformation attributes (trans, rot and scale)
//
//

#include "Image.h"

Image::Image()
{
	trans = ofVec3f(0, 0, 0);
	scale = ofVec3f(1, 1, 1);
	pivot = ofVec3f(0, 0, 0);
	rot = 0;              // degrees 
	bSelected = false;    // not selected 
}

// draw the image using it's current TRS transformations
// do a final translate to offset from pivot point (center of rotation)
//
//
void Image::draw() {

	ofPushMatrix();
		ofTranslate(trans);
		ofRotate(rot);
		ofScale(scale);
		ofTranslate(-pivot.x, -pivot.y);
		ofSetColor(255, 255, 255, 255);
		image.draw(0, 0);
	ofPopMatrix();
}


//  Calculate image (object) coordinates from screen coordinates
//  We we need to take into account the fact that the object is 
//  translated, rotated and shifted to a pivot point (center of rotation)
//
ofVec3f Image::screenToImageSpace(float x, float y) {

	ofVec3f p = ofVec3f(x, y) - trans;
	ofMatrix4x4 m;
	m.rotate(rot, 0, 0, 1);
	return ( (p * m.getInverse()) + pivot);
}
