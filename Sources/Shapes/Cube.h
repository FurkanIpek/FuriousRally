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

	bool texture_map;
	GLuint textures [6];

	void drawSky();

public:
	Cube();
	// Vector trf_pos is the top-right-front point of the cube
	Cube(Color color, Vector center, GLfloat height, GLfloat width, GLfloat depth, bool is_bounding_box = false, bool text_map = false);
	~Cube();

	void setColor(Color clr) { color = clr; }
	void draw();
	void move(GLfloat xv, GLfloat yv, GLfloat zv);
	void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	Vector getCenter() { return center; }
};