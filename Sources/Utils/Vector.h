#pragma once

#include "GL/glew.h"

class Vector {

private:
	GLfloat x, y, z;

public:
	Vector();
	Vector(GLfloat, GLfloat, GLfloat);

	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
	void setX(GLfloat);
	void setY(GLfloat);
	void setZ(GLfloat);

};