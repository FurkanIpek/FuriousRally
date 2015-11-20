#include "Sphere.h"

#include <math.h>

Sphere::Sphere() {}

Sphere::Sphere(Vector v, double r, Color c)
{
	center = v;
	radius = r;
	color = c;
}

Sphere::~Sphere() {}

void Sphere::draw()
{
	glPushMatrix();

	glTranslatef(center.getX(), center.getY(), center.getZ());

	glBegin(GL_LINE_LOOP);
		GLUquadricObj* quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
		gluSphere(quadric, radius, 360, 360);
		gluDeleteQuadric(quadric);
	glEnd();

	glPopMatrix();
}

void Sphere::move(GLfloat xv, GLfloat yv, GLfloat zv)
{
	center.setX(center.getX() + xv);
	center.setY(center.getY() + yv);
	center.setZ(center.getZ() + zv);
}