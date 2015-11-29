#pragma once

#include "Object.h"

class Car : public Object {
private:
	int velocity;
	int acceleration;
	
public:
	Car(Color clr, Vector v, GLfloat h, GLfloat w, GLfloat d);
	~Car();

	Vector center;

	void move(GLfloat xv, GLfloat yv, GLfloat zv);
	void draw();

};