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
	glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
	glTranslatef(center.getX(), center.getY(), center.getZ());	
	glutSolidSphere(radius, 360, 360);
	glPopMatrix();
}

void Sphere::move(GLfloat xv, GLfloat yv, GLfloat zv)
{
	Vector translation_vec(xv, yv, zv);

	center.translate(translation_vec);
}

void Sphere::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	center.rotate(angle, x, y, z);
}