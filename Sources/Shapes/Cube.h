#pragma once

#include "Shape.h"

class Cube : public Shape {

private:
	int height;
	int weight;
	int depth;

public:
	Cube();
	Cube(Color c, int x, int y, int z, int height, int weight, int depth); // x, y, z is the front-top-right point of the cube
	~Cube();

	Color getColor();
	Vector getNormalAtPos(Vector&);
	void draw();
	void move(double, double, double);
};