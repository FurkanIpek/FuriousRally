#pragma once

#include "Cube.h"

class Fire {
private:
	Cube* woods[2];
	Vector center;
	GLuint fire;
	int index;

	void populateFireImage();
	void loadFireTexture();

public:
	Fire(Vector);
	void draw();
};