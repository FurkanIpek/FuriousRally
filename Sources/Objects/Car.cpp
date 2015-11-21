#include "Car.h"

#include "..\Shapes\Circle.h"
#include "..\Shapes\Sphere.h"
#include "..\Shapes\Triangle.h"

Car::Car()
{
	speed = 0;
	acceleration = 0;
	bounding_box = new Cube(Color(0.90f, 0.50f, 0.20f, 0), Vector(0.5f, 0.5f, -10.0f), 1.0f, 1.0f, 3.0f, true);

	Sphere* sphere = new Sphere(Vector(0.5f, 0.05f, -6.0f), 0.5f, Color(0.7f, 0.4f, 0.53f, 0.5f));
	Triangle* triangle = new Triangle(Vector(-0.05f, -0.05f, -6.0f), Vector(0.05f, -0.05f, -6.0f),
		Vector(0.0f, 0.05f, -6.0f), Color(0.56f, 0.15f, 0.80f, 1.0f));
	Cube* cube = new Cube(Color(0.60f, 0.50f, 0.20f, 0), Vector(0.5f, 0.5f, -10.0f), 1.0f, 1.0f, 3.0f);

	parts.push_back(sphere);
	parts.push_back(cube);
	parts.push_back(triangle);

	center = cube->getCenter();
}

Car::~Car() 
{
	delete bounding_box;

	for (int i = 0; i < parts.size(); i++)
		delete parts[i];
}

void Car::move(GLfloat xv, GLfloat yv, GLfloat zv)
{
	for (auto part : parts)
		part->move(xv, yv, zv);
}

void Car::draw()
{
	for (auto part : parts)
		part->draw();
}

void Car::addPart(Shape* new_part)
{
	parts.push_back(new_part);
}