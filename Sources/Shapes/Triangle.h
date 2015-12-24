#pragma once

#include "Shape.h"

class Triangle : public Shape {

private:
	Vector A, B, C;

public:
	Triangle();
	Triangle(Vector a, Vector b, Vector c, Color color);
	~Triangle();

	void draw();
	void translate(Vector translation_vec);
	void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

	Vector getNormal();
};