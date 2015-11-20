#include "Car.h"

#include "..\Shapes\Circle.h"
#include "..\Shapes\Sphere.h"

Car::Car()
{
	speed = 0;
	acceleration = 0;
	bounding_box = new Cube(Color(0.90f, 0.50f, 0.20f, 0), Vector(0.5f, 0.5f, -10.0f), 1.0f, 1.0f, 3.0f, true);
}

Car::~Car() 
{
	delete bounding_box;
}

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