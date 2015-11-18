#pragma once

class Vector {

private:
	double x, y, z;

public:
	Vector();
	Vector(double, double, double);

	double getX();
	double getY();
	double getZ();
	void setX(double);
	void setY(double);
	void setZ(double);
	double Magnitude();
	Vector Normalize();
	Vector Negative();
	double DotProduct(Vector&);
	Vector CrossProduct(Vector&);
	Vector VectorAdd(Vector&);
	Vector VectorMult(double);
};