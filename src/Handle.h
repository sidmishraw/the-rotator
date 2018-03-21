#pragma once
//--------------------------------------------------------------
//
// CS235 - Handle Class (for manipulator handles
//
// Kevin M. Smith - SJSU - 3/17/2018
//
#include "Image.h"


// Support a simple circular handle object.  Only manages drawing
// and it's own position. Includes ::inside() method to test if
// coordinate is inside.
//
class ManipHandle : public BaseObject {
public:
	ManipHandle() {}
	void draw();
	void setPosition(float x, float y) { trans.x = x; trans.y = y; }
	void setColor(ofColor c) { color = c; }
	bool inside(float x, float y) { return ((trans - ofVec2f(x, y)).length() < radius); }
	float radius = 10;
	ofColor color = ofColor::aliceBlue;
};