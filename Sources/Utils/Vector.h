#pragma once

#include "GL/glew.h"

class Vector {

private:
	GLfloat x, y, z;

	void rotateX(GLfloat);
	void rotateY(GLfloat);
	void rotateZ(GLfloat);

public:
	Vector();
	Vector(GLfloat, GLfloat, GLfloat);

	void operator = (Vector& rhs);

	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
	void setX(GLfloat);
	void setY(GLfloat);
	void setZ(GLfloat);

	void translate(Vector);
	void rotate(GLfloat x, GLfloat y, GLfloat z);
	void scale(Vector);

};