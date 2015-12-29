#pragma once

#include "Shape.h"
#include "Triangle.h"

class Cube : public Shape {

private:
	GLfloat height;
	GLfloat width;
	GLfloat depth;
	GLfloat front;
	GLfloat top;
	GLfloat right;

	Vector center;
	Vector points[8];
	Vector normals[6];

	bool is_bounding_box;

public:
	Cube();
	Cube(Color color, Vector center, GLfloat height, GLfloat width, GLfloat depth, bool is_bounding_box = false);
	~Cube();

	void setColor(Color clr) { color = clr; }
	void draw();
	void translate(Vector translation_vec);
	void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	Vector getCenter() { return center; }
	void visibility(bool vis) { is_bounding_box = vis; }
	GLfloat getHeight() { return height; }
	GLfloat getWidth() { return width; }
	GLfloat getDepth() { return depth; }
	Vector* getPoints() { return points; }
};