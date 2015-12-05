#include "Car.h"

Car::Car(Color clr, Vector center, GLfloat h, GLfloat w, GLfloat d) : center(center)
{
	velocity = 0.0f;
	acceleration = 0.0f;
	
	bounding_box = new Cube(Color(0.90f, 0.50f, 0.20f, 0), center, h + 0.5f, w, d, true);

	Sphere* sphere = new Sphere(Vector(center.getX(), center.getY() + h/2, center.getZ()), d/5, Color(0.20f, 0.30f, 0.40f, 0.0f));

	triangle = new Triangle(Vector(center.getX(), center.getY(), center.getZ() + d/2 + 0.1f), Vector(center.getX() + w/4, center.getY() - h/4, center.getZ() + d/2 + 0.1f),
		Vector(center.getX() - w/4, center.getY() - h/4, center.getZ() + d/2 + 0.1f), Color(0.56f, 0.15f, 0.80f, 1.0f));

	Cube* cube = new Cube(clr, center, h, w, d);

	Cylinder* cylinder[5];
	cylinder[0] = new Cylinder(Color::getColor(GRAY), Vector(center.getX() - w / 1.7, center.getY() - h / 2, center.getZ() - d / 2), h / 4, d / 20);
	cylinder[1] = new Cylinder(Color::getColor(GRAY), Vector(center.getX() + w / 2, center.getY() - h / 2, center.getZ() - d / 2), h / 4, d / 20);
	cylinder[2] = new Cylinder(Color::getColor(GRAY), Vector(center.getX() - w / 1.7, center.getY() - h / 2, center.getZ() + d / 2), h / 4, d / 20);
	cylinder[3] = new Cylinder(Color::getColor(GRAY), Vector(center.getX() + w / 2, center.getY() - h / 2, center.getZ() + d / 2), h / 4, d / 20);
	cylinder[4] = new Cylinder(Color::getColor(GRAY), Vector(center.getX() - w/3, center.getY() - h/2, center.getZ() + d/2), h/10, d/20, true);

	parts.push_back(cube);
	parts.push_back(sphere);
	parts.push_back(triangle);
	parts.push_back(bounding_box);

	for (int i = 0; i < 5; i++)
		parts.push_back(cylinder[i]);
}

Car::~Car() 
{
	delete bounding_box;

	for (unsigned short i = 0; i < parts.size(); i++)
		delete parts[i];
}

void Car::move(GLfloat xv, GLfloat yv, GLfloat zv)
{
	//acceleration += 0.0002f;
	// TODO velocity and acceleration calculations
	for (auto part : parts)
		part->move(xv, yv, zv - velocity);

	center.translate(Vector(xv, yv, zv));
}

void Car::draw()
{
	if (acceleration > 0)
		triangle->setColor(Color::getColor(GREEN));
	else
		triangle->setColor(Color::getColor(RED));

	velocity += acceleration;

	for (auto part : parts)
		part->draw();
}