#pragma once

#include "Object.h"

class Car : public Object {
private:
	int speed;
	int acceleration;
	
public:
	Car();
	~Car();

	Vector center;

	void move(GLfloat, GLfloat, GLfloat);
	void draw();
	void addPart(Shape*);

};