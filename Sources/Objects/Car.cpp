#include "Car.h"
#include "..\Utils\Constants.h"

Car::Car(Color clr, Vector center, GLfloat h, GLfloat w, GLfloat d) : center(center)
{
	velocity = 0.0f;
	acceleration = 0.0f;
	direction.setX(0), direction.setY(0), direction.setZ(-1);
	speedLimit = 0.80f;
	deccelerating = false;
	state = maxTurn / 2;
	
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
	parts.push_back(bounding_box);
	parts.push_back(sphere);
	parts.push_back(triangle);

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

	if (velocity >= speedLimit)
		velocity = speedLimit;

	if (velocity < -speedLimit / 10)
		velocity = -speedLimit / 10;
	
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
		if (velocity > 0)
			acceleration = -5 * acc;
		else
			acceleration = -acc;
	}
	
	if (velocity <= 0.0f && !deccelerating)
	{
		acceleration = 0.0f;
		velocity = 0.0f;
	}
}

void Car::turn(TURN side)
{
	if (velocity == 0.0f) return;
	GLfloat ang;

	if (side == left)
	{
		if (state >= 1) state--;
		else return;
		// positive angle
		ang = turnAngle;
	}
	else
	{
		if (state <= maxTurn) state++;
		else return;
		// negative angle
		ang = -turnAngle;
	}

	for (int i = 0; i < parts.size(); i++)//(auto part : parts)
	{
		//if (i == 4 || i == 5) ang *= 1.25f;
		parts[i]->translate(center.negative());
		parts[i]->rotate(ang, 0.0f, 1.0f, 0.0f);
		parts[i]->translate(center);
		//if (i == 4 || i == 5) ang /= 1.25f;
	}
	direction.rotate(ang, 0.0f, 1.0f, 0.0f);
}

void Car::straighten()
{
	int dif = state - maxTurn / 2;

	if (dif > 0)
		while (dif-- != 0)
			turn(left);
	else if (dif < 0)
		while (dif++ != 0)
			turn(right);
}

void Car::checkCollision(Car* other)
{
	Cube* bnd_bx = other->getBoundingBox();
	Vector otherCtr = bnd_bx->getCenter(), center = this->bounding_box->getCenter();

	GLfloat zd = abs(otherCtr.getZ() - center.getZ()),
		yd = abs(otherCtr.getY() - center.getY()),
		xd = abs(otherCtr.getX() - center.getX());

	bool z = 0, y = 0, x = 0;

	if (zd < (bnd_bx->getDepth() / 2 + this->bounding_box->getDepth() / 2)) z = true;

	if (yd < (bnd_bx->getHeight() / 2 + this->bounding_box->getHeight() / 2)) y = true;

	if (xd < (bnd_bx->getWidth() / 2 + this->bounding_box->getWidth() / 2)) x = true;

	if (x && y && z) // if there is a collision
	{
		if (z && zd < bnd_bx->getDepth() / 4) // side to side crash
		{
			this->setVelocity(this->getVelocity() - 0.1f);
			other->setVelocity(other->getVelocity() - 0.1f);

			if (other->getCenter().getX() < this->getCenter().getX()) // other car is at the right
			{
				other->turn(right);
				this->turn(left);
			}
			else
			{
				other->turn(right);
				this->turn(left);
			}
		}
		else // one car is behind the other, slow down the car behind, speed up the car front
		{
			GLfloat amount = 0.05f;
			if (other->getCenter().getZ() < this->getCenter().getZ()) // other car is at the front
			{
				other->setVelocity(other->getVelocity() + amount);
				this->setVelocity(this->getVelocity() - amount);
			}
			else
			{
				other->setVelocity(other->getVelocity() - amount);
				this->setVelocity(this->getVelocity() + amount);
			}
		}
	}
}

bool Car::checkCollision(Cube* cube)
{
	Vector otherCtr = cube->getCenter(), center = this->bounding_box->getCenter();

	GLfloat zd = abs(otherCtr.getZ() - center.getZ()),
		yd = abs(otherCtr.getY() - center.getY()),
		xd = abs(otherCtr.getX() - center.getX());

	bool z = 0, y = 0, x = 0;

	if (zd < (cube->getDepth() / 2 + this->bounding_box->getDepth() / 2)) z = true;

	if (yd < (cube->getHeight() / 2 + this->bounding_box->getHeight() / 2)) y = true;

	if (xd < (cube->getWidth() / 2 + this->bounding_box->getWidth() / 2)) x = true;

	return x && y && z;
}