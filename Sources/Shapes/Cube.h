#pragma once

#include "Shape.h"

class Cube : public Shape {

private:
	GLfloat height;
	GLfloat width;
	GLfloat depth;
	GLfloat front;
	GLfloat top;
	GLfloat right;

	Vector points[8];

	bool is_bounding_box;

public:
	Cube();
	// Vector trf_pos is the top-right-front point of the cube
	Cube(Color color, Vector trf_pos, GLfloat height, GLfloat width, GLfloat depth, bool is_bounding_box = false);
	~Cube();

	Color getColor() { return color; }
	void setColor(Color c) { color = c; }
	void draw();
	void move(GLfloat, GLfloat, GLfloat);

	Vector getCenter() { return Vector(top - width / 2, right - height / 2, front - depth / 2); }
};