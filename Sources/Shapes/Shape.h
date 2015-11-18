#pragma once

#include "GL\glew.h"
#include "GL\freeglut.h"

#include "..\Utils\Vector.h"
#include "..\Utils\Color.h"

class Shape {
protected:
	Color color;

public:
	virtual Color getColor() = 0;
	virtual Vector getNormalAtPos(Vector&) = 0;
	virtual void draw() = 0;
	virtual void move(double, double, double) = 0;
};