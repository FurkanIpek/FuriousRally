#pragma once

#include "GL\glew.h"
#include "GL\freeglut.h"

#include "..\Utils\Vector.h"
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
	virtual void translate(Vector translation_vec) = 0;
	virtual void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) = 0;
};