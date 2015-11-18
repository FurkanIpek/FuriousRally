#pragma once

#include "Shape.h"

class Triangle: public Shape {

private:
	Vector A, B, C;
	Vector edge_1, edge_2;

public:
	Triangle();
	Triangle(Vector a, Vector b, Vector c, Color color);
	~Triangle();

	Color getColor() { return color; }
	void move(double, double, double);
	void draw();
	Vector getNormalAtPos(Vector&);
};