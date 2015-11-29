#include "Car.h"

#include "..\Shapes\Sphere.h"
#include "..\Shapes\Cylinder.h"
#include "..\Shapes\Triangle.h"

Car::Car(Color clr, Vector v, GLfloat h, GLfloat w, GLfloat d)
{
	velocity = 0;
	acceleration = 0;
	// TODO calculate bounding box
	bounding_box = new Cube(Color(0.90f, 0.50f, 0.20f, 0), Vector(0.5f, 0.5f, -10.0f), 1.0f, 1.0f, 3.0f, true);

	Sphere* sphere = new Sphere(Vector(v.getX() - w/2, v.getY(), v.getZ() - d/2), d/5, Color(0.20f, 0.30f, 0.40f, 0.0f));

	Triangle* triangle = new Triangle(Vector(v.getX() - w / 2, v.getY() - h / 2, v.getZ() + 0.1f), Vector(v.getX() - w / 2 + w / 8, v.getY() - h / 2 - w / 8, v.getZ() + 0.1f),
		Vector(v.getX() - w / 2 - w / 8, v.getY() - h / 2 - w / 8, v.getZ() + 0.1f), Color(0.56f, 0.15f, 0.80f, 1.0f));

	Cube* cube = new Cube(clr, v, h, w, d);

	Cylinder* cylinder[4];
	cylinder[0] = new Cylinder(clr, 0.5, 0.5);
	cylinder[1] = new Cylinder(clr, 0.8, 0.8);
	cylinder[2] = new Cylinder();
	cylinder[3] = new Cylinder();

	parts.push_back(cube);
	parts.push_back(sphere);
	parts.push_back(triangle);

	/*for (int i = 0; i < 4; i++)
		parts.push_back(cylinder[i]);*/

	center = cube->getCenter();
}

Car::~Car() 
{
	delete bounding_box;

	for (unsigned short i = 0; i < parts.size(); i++)
		delete parts[i];
}

void Car::move(GLfloat xv, GLfloat yv, GLfloat zv)
{
	// TODO velocity and acceleration calculations
	for (auto part : parts)
		part->move(xv, yv, zv);

	center.translate(Vector(xv, yv, zv));
}

void Car::draw()
{
	for (auto part : parts)
		part->draw();
}