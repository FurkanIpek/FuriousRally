#include "Cylinder.h"

Cylinder::Cylinder() {}

Cylinder::Cylinder(Color clr, GLfloat r, GLfloat l) : r(r), l(l) { color = clr; }

Cylinder::~Cylinder() {}

void Cylinder::draw()
{
	float x, y, z; 

	glBegin(GL_QUAD_STRIP);

	glColor3f(153.0f / 256.0f, 204.0f / 256.0f, 0.98f);

	for (int d = 0; d <= 362; d++)
	{
		x = r*cos(cn*d);
		z = r*sin(cn*d);
		y = 0;
		glVertex3f(x, y, z);

		y = l;
		glVertex3f(x, y, z);
	}

	glEnd();
}

void Cylinder::move(GLfloat xv, GLfloat yv, GLfloat zv)
{

}