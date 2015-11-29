#pragma once

#include "Shape.h"

class Cylinder : public Shape {
private:
	GLfloat r, l;
public:
	Cylinder();
	Cylinder(Color color, GLfloat r, GLfloat l);
	~Cylinder();

	void draw();
	void move(GLfloat xv, GLfloat yv, GLfloat zv);
};