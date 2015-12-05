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

	GLfloat magnitude();
	Vector normalize();
	Vector negative();
	GLfloat dotProduct(Vector&);
	Vector crossProduct(Vector&);
	Vector vectorAdd(Vector&);
	Vector vectorMult(GLfloat);

	void translate(Vector translation_vector);
	void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void scale(Vector scaling_vector);

};