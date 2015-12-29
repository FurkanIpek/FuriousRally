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

	GLfloat speedLimit;
	bool deccelerating;
	// used for turning the car
	int state;
	
public:
	Car(Color clr, Vector center, GLfloat h, GLfloat w, GLfloat d);
	~Car();

	void move();
	void move(Vector);
	void accelerate();
	void decelerate(bool anchors);
	void turn(TURN side);
	void draw();
	Cube* getBoundingBox() { return bounding_box; }
	GLfloat getVelocity() { return velocity; }
	void setVelocity(GLfloat velocity) { this->velocity = velocity; }
	void setSpeedLimit(GLfloat limit) { speedLimit = limit; }
	Vector getCenter() { return center; }
	void checkCollision(Car* other);
	bool checkCollision(Cube* cube);
	void straighten();
};