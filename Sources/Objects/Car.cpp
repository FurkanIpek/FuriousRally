#include "Car.h"

#define acc 0.005f

Car::Car(Color clr, Vector center, GLfloat h, GLfloat w, GLfloat d) : center(center)
{
	velocity = 0.0f;
	acceleration = 0.0f;
	direction.setX(0), direction.setY(0), direction.setZ(-1);
	deccelerating = false;
	
	bounding_box = new Cube(clr, center, h + 0.5f, w, d, true);

	Sphere* sphere = new Sphere(Vector(center.getX(), center.getY() + h/2, center.getZ()), d/5, Color(0.20f, 0.30f, 0.40f, 0.0f));
	// used as a stop light
	triangle = new Triangle(Vector(center.getX(), center.getY(), center.getZ() + d/2 + 0.001f), Vector(center.getX() + w/4, center.getY() - h/4, center.getZ() + d/2 + 0.001f),
		Vector(center.getX() - w/4, center.getY() - h/4, center.getZ() + d/2 + 0.001f), Color(0.56f, 0.15f, 0.80f, 1.0f));

	Cube* cube = new Cube(clr, center, h, w, d);

	Cylinder* cylinder[5];
	cylinder[0] = new Cylinder(Color::getColor(GRAY), Vector(center.getX() - w / 1.7, center.getY() - h / 2, center.getZ() - d / 2), h / 4, d / 20);
	cylinder[1] = new Cylinder(Color::getColor(GRAY), Vector(center.getX() + w / 2, center.getY() - h / 2, center.getZ() - d / 2), h / 4, d / 20);
	cylinder[2] = new Cylinder(Color::getColor(GRAY), Vector(center.getX() - w / 1.7, center.getY() - h / 2, center.getZ() + d / 2), h / 4, d / 20);
	cylinder[3] = new Cylinder(Color::getColor(GRAY), Vector(center.getX() + w / 2, center.getY() - h / 2, center.getZ() + d / 2), h / 4, d / 20); // wheels
	cylinder[4] = new Cylinder(Color::getColor(GRAY), Vector(center.getX() - w/3, center.getY() - h/2, center.getZ() + d/2), h/10, d/20, true); // exhaust

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

void Car::move()
{
	GLfloat total = abs(direction.getX()) + abs(direction.getY()) + abs(direction.getZ());
	GLfloat x = (abs(direction.getX()) / total),
		y = -velocity * (abs(direction.getY()) / total),
		z = -velocity * (abs(direction.getZ()) / total);
	if (direction.getX() > 0) x *= velocity;
	else x *= -velocity;
	Vector vec(x, y, z);

	for (auto part : parts)
		part->translate(vec);

	center.translate(vec);
}

void Car::move(Vector vec)
{
	for (auto part : parts)
		part->translate(vec);

	center.translate(vec);
}

/* This function is called in every frame, so some updates are also being done in this function */
void Car::draw()
{
	if (deccelerating)
		triangle->setColor(Color::getColor(RED));
	else
		triangle->setColor(Color::getColor(GREEN));

	velocity += acceleration;

	if (velocity >= 0.80f)
		velocity = 0.80f;
	
	for (auto part : parts)
		part->draw();
}

void Car::accelerate()
{
	deccelerating = false;
	acceleration = acc;
}

void Car::decelerate(bool anchors)
{
	acceleration = -acc/0.90f;

	if (anchors)
	{
		deccelerating = true;
		acceleration = -5*acc;
	}
	// bizde geri vites yok :D
	if (velocity <= 0.0f)
	{
		acceleration = 0.0f;
		velocity = 0.0f;
	}
}

void Car::turn(TURN side)
{
	// 0 -> 2x left, 1 -> left, 2 -> straight, 3 -> right, 4 -> 2x right
	static int state = 2;
	static GLfloat angle = 3.5f;

	if (velocity == 0.0f) return;

	if (side == left)
	{
		if (state >= 1) state--;
		else return;
		// positive angle
		angle = abs(angle);
	}
	else
	{
		if (state <= 3) state++;
		else return;
		// negative angle
		angle = -abs(angle);
	}

	for (auto part : parts)
	{
		part->translate(center.negative());
		part->rotate(angle, 0.0f, 1.0f, 0.0f);
		part->translate(center);
	}
	direction.rotate(angle, 0.0f, 1.0f, 0.0f);
}