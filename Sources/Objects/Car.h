#pragma once

#include "Object.h"

#include "..\Shapes\Sphere.h"
#include "..\Shapes\Cylinder.h"
#include "..\Shapes\Triangle.h"

class Car : public Object {
private:
	GLfloat velocity;
	GLfloat acceleration;
	Triangle* triangle;
	Vector center;
	
public:
	Car(Color clr, Vector center, GLfloat h, GLfloat w, GLfloat d);
	~Car();

	void move(GLfloat xv, GLfloat yv, GLfloat zv);
	void draw();
	GLfloat getVelocity() { return velocity; }
	Vector getCenter() { return center; }

};