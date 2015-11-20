#include "Vector.h"
#include <math.h>

Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(GLfloat x, GLfloat y, GLfloat z): x(x), y(y), z(z) {}

GLfloat Vector::getX()
{
	return x;
}

GLfloat Vector::getY()
{
	return y;
}

GLfloat Vector::getZ()
{
	return z;
}

void Vector::setX(GLfloat v)
{
	x = v;
}

void Vector::setY(GLfloat v)
{
	y = v;
}

void Vector::setZ(GLfloat v)
{
	z = v;
}