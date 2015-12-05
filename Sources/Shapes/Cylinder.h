#pragma once

#include "Shape.h"
// TODO cylinder is not fully developed
class Cylinder : public Shape {
private:
	GLfloat radius, height;
	Vector coordinates;
	bool exhaust;

public:
	Cylinder();
	Cylinder(Color color, Vector coordinates, GLfloat radius, GLfloat height, bool exhaust = false);
	~Cylinder();

	void draw();
	void move(GLfloat xv, GLfloat yv, GLfloat zv);
	void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
};