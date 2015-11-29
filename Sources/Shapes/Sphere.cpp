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

	glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());

	glBegin(GL_LINE_LOOP);
		GLUquadricObj* quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluSphere(quadric, radius, 360, 360);
		gluDeleteQuadric(quadric);
	glEnd();
	
	//glutSolidSphere(radius, 360, 360);

	glPopMatrix();
}

void Sphere::move(GLfloat xv, GLfloat yv, GLfloat zv)
{
	Vector translation_vec(xv, yv, zv);

	center.translate(translation_vec);
}