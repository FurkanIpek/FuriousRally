#pragma once

#include "Shape.h"

class Triangle : public Shape {

private:
	Vector A, B, C;

public:
	Triangle();
	Triangle(Vector a, Vector b, Vector c, Color color);
	~Triangle();

	void move(GLfloat, GLfloat, GLfloat);
	void draw();
	void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

	Vector getNormal();
};