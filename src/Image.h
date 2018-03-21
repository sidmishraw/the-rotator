//--------------------------------------------------------------
//
//  CS235 - User Interface Design - Kevin M. Smith
//
//  Class wrapper for an image
// 
//  Simple class wrapper to store an ofImage with
//  tranformation attributes (trans, rot and scale)
//
//  This example is a translate/scale manipulator
//
//

#pragma once
#include "ofMain.h"

class BaseObject {
public:
	ofVec2f trans, scale;
	float	rot;
	bool	bSelected;
	ofVec2f pivot;
};

class Image : public BaseObject {

public:
	Image();
	ofImage image;
	void draw();    // x and y is the offset to rotation point
	void setPivot(const ofVec3f &point) { pivot = point;  }
	ofVec3f screenToImageSpace(float x, float y);
	ofMatrix4x4 m;
};


