#include "Triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(Vector a, Vector b, Vector c, Color clr) : A(a), B(b), C(c)
{
	edge_1 = B.VectorAdd(A.Negative());
	edge_2 = A.VectorAdd(C.Negative());

	color = clr;
}

Triangle::~Triangle() {}

void Triangle::draw()
{
	glColor3f(color.getRed(), color.getGreen(), color.getBlue());

	glBegin(GL_TRIANGLES);

	glVertex3f((GLfloat)A.getX(), (GLfloat)A.getY(), (GLfloat)A.getZ());    // A
	glVertex3f((GLfloat)B.getX(), (GLfloat)B.getY(), (GLfloat)B.getZ());    // B
	glVertex3f((GLfloat)C.getX(), (GLfloat)C.getY(), (GLfloat)C.getZ());    // C
	// piramit
	//glVertex3f(-1.0f, -0.5f, 0.5f);    // A
	//glVertex3f(1.0f, -0.5f, 0.5f);    // B

	//glVertex3f(0.0f, 0.5f, 0.5f);    // C
	//glVertex3f(1.5f, 0.0f, 0.5f);     // D
	//glVertex3f(2.0f, -1.5f, 0.5f);     // E

	glEnd();
}

void Triangle::move(double x, double y, double z)
{
	A.setX(A.getX() + x);
	B.setX(C.getX() + x);
	C.setX(C.getX() + x);
	
	A.setY(A.getY() + y);
	B.setY(C.getY() + y);
	C.setY(C.getY() + y);

	A.setZ(A.getZ() + z);
	B.setZ(C.getZ() + z);
	C.setZ(C.getZ() + z);
}

Vector Triangle::getNormalAtPos(Vector& vect)
{
	Vector normal = edge_1.CrossProduct(edge_2).Normalize();

	return normal;
}