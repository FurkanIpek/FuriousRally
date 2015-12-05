#pragma once

#include "GL\glew.h"
#include "GL\freeglut.h"

#include "..\Utils\Vector.h" // is used by shapes(cube, sphere etc) - included here once
#include "..\Utils\Color.h"

#define cn 3.14/180
#define PI 3.14

class Shape {
protected:
	Color color;

public:
	Color getColor() { return color; }
	void setColor(Color clr) { color = clr; }

	virtual void draw() = 0;
	virtual void move(GLfloat xv, GLfloat yv, GLfloat zv) = 0;
	virtual void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) = 0;
};