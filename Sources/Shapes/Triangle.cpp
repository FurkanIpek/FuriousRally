#include "Triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(Vector a, Vector b, Vector c, Color clr) : A(a), B(b), C(c) { color = clr; }

Triangle::~Triangle() {}

void Triangle::draw()
{
	Vector normal = getNormal();
	glPushMatrix();

	glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());

	glBegin(GL_TRIANGLES);
		glNormal3f(normal.getX(), normal.getY(), normal.getZ());
		glVertex3f(A.getX(), A.getY(), A.getZ());
		glVertex3f(B.getX(), B.getY(), B.getZ());
		glVertex3f(C.getX(), C.getY(), C.getZ());
	glEnd();

	glPopMatrix();
}

Vector Triangle::getNormal()
{
	Vector edge_1 = B.vectorAdd(A.negative());
	Vector edge_2 = A.vectorAdd(C.negative());
	Vector normal = edge_1.crossProduct(edge_2).normalize();

	return normal;
}

void Triangle::translate(Vector translation_vec)
{
	A.translate(translation_vec);
	B.translate(translation_vec);
	C.translate(translation_vec);
}

void Triangle::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	A.rotate(angle, x, y, z);
	B.rotate(angle, x, y, z);
	C.rotate(angle, x, y, z);
}