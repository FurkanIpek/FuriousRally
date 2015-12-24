#pragma once

#include "Object.h"

#include "..\Shapes\Sphere.h"
#include "..\Shapes\Cylinder.h"
#include "..\Shapes\Triangle.h"

enum TURN {left, right};

class Car : public Object {
private:
	GLfloat velocity;
	GLfloat acceleration;
	Triangle* triangle;
	Vector center;
	Vector direction;

	bool deccelerating;
	
public:
	Car(Color clr, Vector center, GLfloat h, GLfloat w, GLfloat d);
	~Car();

	void move();
	void move(Vector);
	void accelerate();
	void decelerate(bool anchors);
	void turn(TURN side);
	void draw();
	GLfloat getVelocity() { return velocity; }
	Vector getCenter() { return center; }

};