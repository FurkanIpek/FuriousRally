#pragma once

#include "Shape.h"

class Sphere: public Shape {

private:
	Vector center;
	double radius;

public:
	Sphere();
	Sphere(Vector, double, Color);
	~Sphere();

	double pos() { return center.getZ(); }
	void draw();
	void translate(Vector translation_vec);
	void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
};