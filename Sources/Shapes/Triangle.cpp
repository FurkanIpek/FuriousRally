#include "Triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(Vector a, Vector b, Vector c, Color clr) : A(a), B(b), C(c) { color = clr; }

Triangle::~Triangle() {}

void Triangle::draw()
{
	glPushMatrix();
	
	glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());

	glBegin(GL_TRIANGLES);
		glVertex3f(A.getX(), A.getY(), A.getZ());
		glVertex3f(B.getX(), B.getY(), B.getZ());
		glVertex3f(C.getX(), C.getY(), C.getZ());
	glEnd();

	glPopMatrix();
}

void Triangle::move(GLfloat xv, GLfloat yv, GLfloat zv)
{
	Vector translation_vec(xv, yv, zv);

	A.translate(translation_vec);
	B.translate(translation_vec);
	C.translate(translation_vec);
}