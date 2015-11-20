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

	bool is_bounding_box;

public:
	Cube();
	Cube(Color color, Vector trf_pos, GLfloat height, GLfloat width, GLfloat depth, bool is_bounding_box = false); // Vector(x,y,z) is the top-right-front point of the cube
	~Cube();

	Color getColor() { return color; }
	void setColor(Color c) { color = c; }
	void draw();
	void move(GLfloat, GLfloat, GLfloat);
};