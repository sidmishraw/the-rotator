//--------------------------------------------------------------
//
// CS235 - Handle class (for manipulator handles)
//
// Kevin M. Smith - SJSU - 3/17/2018
//

#include "Handle.h"

// Draw handles - circles with black outline
//
void ManipHandle::draw() {
	ofFill();
	ofSetColor(color);
	ofDrawCircle(trans.x, trans.y, radius);
	ofNoFill();
	ofSetColor(ofColor::black);
	ofDrawCircle(trans.x, trans.y, radius);
}
