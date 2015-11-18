#pragma once

#include "Shape.h"

class Circle : public Shape {

private:
	Vector center;
	double radius;

public:
	Circle();
	Circle(Vector, double, Color);
	~Circle();

	Color getColor();
	Vector getNormalAtPos(Vector&);
	void draw();
	void move();
};