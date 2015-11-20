#pragma once

#include "GL\glew.h"
#include "GL\freeglut.h"

#include "..\Utils\Vector.h" // is used by shapes(cube, sphere etc) - included here once
#include "..\Utils\Color.h"

class Shape {
protected:
	Color color;

public:
	virtual void draw() = 0;
	virtual void move(GLfloat, GLfloat, GLfloat) = 0;
};