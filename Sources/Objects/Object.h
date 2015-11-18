#pragma once

#include "..\Shapes\Shape.h"

#include <vector>

class Object {

protected:
	// All shapes belonging to this object
	std::vector<Shape*> parts;

public:
	virtual void draw() = 0;
	virtual void move() = 0;

};