#include "Vector.h"
#include <math.h>

Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(double x, double y, double z): x(x), y(y), z(z) {}

double Vector::getX()
{
	return x;
}

double Vector::getY()
{
	return y;
}

double Vector::getZ()
{
	return z;
}

void Vector::setX(double v)
{
	x = v;
}

void Vector::setY(double v)
{
	y = v;
}

void Vector::setZ(double v)
{
	z = v;
}
	
double Vector::Magnitude() 
{
	return sqrt(x*x + y*y + z*z);
}
	
Vector Vector::Normalize() 
{
	double magnitude = this->Magnitude();

	return Vector(x/magnitude, y/magnitude, z/magnitude);
}
	
Vector Vector::Negative() 
{
	return Vector(-x, -y, -z);
}
	
double Vector::DotProduct(Vector& vect) 
{
	return getX()*vect.getX() + getY()*vect.getY() + getZ()*vect.getZ();
}
	
Vector Vector::CrossProduct(Vector& vect) 
{
	return Vector(getY()*vect.getZ() - getZ()*vect.getY(), 
		getZ()*vect.getX() - getX()*vect.getZ(), getX()*vect.getY() - getY()*vect.getX());
}
	
Vector Vector::VectorAdd(Vector& vect) 
{
	return Vector(getX() + vect.getX(), getY() + vect.getY(), getZ() + vect.getZ());
}

Vector Vector::VectorMult(double scalar) 
{
	return Vector(getX()*scalar, getY()*scalar, getZ()*scalar);
}