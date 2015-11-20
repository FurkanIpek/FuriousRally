#pragma once

#include "Shape.h"

class Triangle: public Shape {

private:
	Vector A, B, C;

public:
	Triangle();
	Triangle(Vector a, Vector b, Vector c, Color color);
	~Triangle();

	Color getColor() { return color; }
	void move(GLfloat, GLfloat, GLfloat);
	void draw();
};