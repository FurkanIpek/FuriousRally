#pragma once

#include "Vector.h"

class Camera {
private:
	Vector position, direction, right, down;

public:
	Camera() {};
	Camera(Vector pos, Vector dir, Vector r, Vector dn) : position(pos), direction(dir), right(r), down(dn) {}

	Vector getCameraPosition () { return position; }
	Vector getCameraDirection () { return direction; }
	Vector getCameraRight () { return right; }
	Vector getCameraDown () { return down; }
};