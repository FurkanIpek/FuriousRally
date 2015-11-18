#pragma once

#include "Object.h"

class Car : public Object {
private:
	int speed;
	int acceleration;

public:
	Car();
	~Car();

	void move();
	void draw();
};