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
	void addPart(Shape* part) { parts.push_back(part); }

	virtual void draw() = 0;
	virtual void move(GLfloat xv, GLfloat yv, GLfloat zv) = 0;

};