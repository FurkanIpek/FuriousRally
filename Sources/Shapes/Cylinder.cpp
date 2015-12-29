#include "Cylinder.h"

GLfloat a, xv, yv, zv;

Cylinder::Cylinder() {}

Cylinder::Cylinder(Color clr, Vector coor, GLfloat radius, GLfloat h, bool exhaust) 
	: coordinates(coor), radius(radius), height(h), exhaust(exhaust) 
{
	x = y = z = 0.0f;
	angle = 0.0f;
	rotated = false;
	color = clr;
}

Cylinder::~Cylinder() {}

void Cylinder::draw()
{
	glPushMatrix();
	glColor3f(color.getRed(), color.getGreen(), color.getBlue());
	glTranslatef(coordinates.getX(), coordinates.getY(), coordinates.getZ());
	if (!exhaust)
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glutSolidCylinder(radius, height, 360, 360);
	
	glPopMatrix();
}

void Cylinder::translate(Vector translation_vec)
{
	coordinates.translate(translation_vec);
}

void Cylinder::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	this->angle += angle;
	rotated = true;
	coordinates.rotate(angle, x, y, z);
}