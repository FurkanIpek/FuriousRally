#include "Car.h"

#include "..\Shapes\Circle.h"
#include "..\Shapes\Sphere.h""

Car::Car()
{
	speed = 0;
	acceleration = 0;
}

Car::~Car() {}

void Car::move()
{
	for (auto part : parts)
		part->move(1, 1, 1);
}

void Car::draw()
{
	for (auto part : parts)
		part->draw();
}