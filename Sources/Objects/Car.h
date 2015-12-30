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
	GLfloat turningAngle;
	GLfloat speedLimit;
	bool deccelerating;
	// used for turning the car
	int state;
	bool isUser;
	
public:
	Car(Color clr, Vector center, GLfloat h, GLfloat w, GLfloat d, bool user = false);
	~Car();

	void move();
	void move(Vector);
	void accelerate();
	void decelerate(bool anchors);
	bool turn(TURN side);
	void draw();
	Cube* getBoundingBox() { return bounding_box; }
	GLfloat getVelocity() { return velocity; }
	void setVelocity(GLfloat velocity) { this->velocity = velocity; }
	void setAngle(GLfloat ang) { turningAngle = ang; }
	void setSpeedLimit(GLfloat limit) { speedLimit = limit; }
	Vector getCenter() { return center; }
	Vector getDirection() { return direction; }
	GLfloat getSpeedLimit() { return speedLimit; }
	void checkCollision(Car* other);
	bool checkCollision(Cube* cube);
	void straighten();
	void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void translate(Vector vec);
	bool carIsUser() { return isUser; }
};