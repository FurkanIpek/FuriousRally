#pragma once

#include "..\Shapes\Shape.h"
#include "..\Shapes\Cube.h"

#include <vector>

class Object {

protected:
	// All shapes belonging to an object
	std::vector<Shape*> parts;
	Cube* bounding_box;

public:
	virtual void draw() = 0;
	virtual void move(GLfloat, GLfloat, GLfloat) = 0;
	virtual void addPart(Shape*) = 0;

};