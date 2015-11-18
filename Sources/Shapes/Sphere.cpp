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
	glBegin(GL_LINE_LOOP);
		GLUquadricObj* quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		glTranslated(center.getX(), center.getY(), center.getZ());
		glColor3d(color.getRed(), color.getGreen(), color.getBlue());
		gluSphere(quadric, radius, 100, 100);
		gluDeleteQuadric(quadric);
	glEnd();
	/*glPushMatrix();
		glTranslated(0.0 + center.getX(), 1.2 + center.getY(), -6 + center.getZ());
		glColor3d(color.getRed(), color.getGreen(), color.getBlue());
		glutSolidSphere(radius, 50, 50);
	glPopMatrix();*/
}

void Sphere::move(double xv, double yv, double zv)
{
	center.setX(center.getX() + xv);
	center.setY(center.getY() + yv);
	center.setZ(center.getZ() + zv);
}

Vector Sphere::getNormalAtPos(Vector& vec)
{
	return vec.VectorAdd(center.Negative()).Normalize();;
}