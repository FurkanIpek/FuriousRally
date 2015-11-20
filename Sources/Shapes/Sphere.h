#pragma once

#include "Shape.h"

class Sphere: public Shape {

private:
	Vector center;
	double radius;

	const double PI = 3.1415926535897;

public:
	Sphere();
	Sphere(Vector, double, Color);
	~Sphere();

	Color getColor() { return color; }
	double pos() { return center.getZ(); }
	void draw();
	void move(GLfloat, GLfloat, GLfloat);
};