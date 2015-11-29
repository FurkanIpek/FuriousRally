#include "Vector.h"
#include <math.h>

const static double PI = 3.1415926535897;

Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(GLfloat x, GLfloat y, GLfloat z): x(x), y(y), z(z) {}

void Vector::operator =(Vector& rhs)
{
	x = rhs.getX();
	y = rhs.getY();
	z = rhs.getZ();
}

GLfloat Vector::getX()
{
	return x;
}

GLfloat Vector::getY()
{
	return y;
}

GLfloat Vector::getZ()
{
	return z;
}

void Vector::setX(GLfloat v)
{
	x = v;
}

void Vector::setY(GLfloat v)
{
	y = v;
}

void Vector::setZ(GLfloat v)
{
	z = v;
}

void Vector::translate(Vector vec)
{
	GLfloat translation[4][4] =
	{
		{ 1.0f, 0.0f, 0.0f, vec.getX() },
		{ 0.0f, 1.0f, 0.0f, vec.getY() },
		{ 0.0f, 0.0f, 1.0f, vec.getZ() },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	GLfloat cur_matrix [4] = { x, y, z, 1.0f};
	GLfloat result [4] = {0.0f, 0.0f, 0.0f, 0.0f};

	for (int i = 0; i < 4; i++)
			for (int k = 0; k < 4; k++)
				result[i] = result[i] + translation[i][k] * cur_matrix[k];

	x = result[0];
	y = result[1];
	z = result[2];
}

void Vector::rotateX(GLfloat alfa)
{
	GLfloat sin_alfa = (GLfloat) sin(alfa*PI/180),
			cos_alfa = (GLfloat) cos(alfa*PI/180);

	GLfloat rotation[4][4] =
	{
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, cos_alfa, -sin_alfa, 0.0f },
		{ 0.0f, sin_alfa, cos_alfa, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	GLfloat cur_matrix[4] = { x, y, z, 1.0f };
	GLfloat result[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	for (int i = 0; i < 4; i++)
		for (int k = 0; k < 4; k++)
			result[i] = result[i] + rotation[i][k] * cur_matrix[k];

	x = result[0];
	y = result[1];
	z = result[2];
}

void Vector::rotateY(GLfloat alfa)
{
	GLfloat sin_alfa = (GLfloat)sin(alfa*PI / 180),
		cos_alfa = (GLfloat)cos(alfa*PI / 180);

	GLfloat rotation[4][4] =
	{
		{ cos_alfa, 0.0f, sin_alfa, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ -sin_alfa, 0.0f, cos_alfa, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	GLfloat cur_matrix[4] = { x, y, z, 1.0f };
	GLfloat result[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	for (int i = 0; i < 4; i++)
		for (int k = 0; k < 4; k++)
			result[i] = result[i] + rotation[i][k] * cur_matrix[k];

	x = result[0];
	y = result[1];
	z = result[2];
}

void Vector::rotateZ(GLfloat alfa)
{
	GLfloat sin_alfa = (GLfloat)sin(alfa*PI / 180),
		cos_alfa = (GLfloat)cos(alfa*PI / 180);

	GLfloat rotation[4][4] =
	{
		{ cos_alfa, -sin_alfa, 0.0f, 0.0f },
		{ sin_alfa, cos_alfa, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	GLfloat cur_matrix[4] = { x, y, z, 1.0f };
	GLfloat result[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	for (int i = 0; i < 4; i++)
		for (int k = 0; k < 4; k++)
			result[i] = result[i] + rotation[i][k] * cur_matrix[k];

	x = result[0];
	y = result[1];
	z = result[2];
}
// TODO does translation * cur_mat  and then rotation * cur_mat work? Also check the correctness of the following arrangement
void Vector::rotate(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat temp_x = x,
		temp_y = y,
		temp_z = z;

	// cismi orijine taþý
	if (x != 0.0f)
		rotateX(x);

	if (y != 0.0f)
		rotateY(y);

	if (z != 0.0f)
		rotateZ(z);
}

void Vector::scale(Vector vec)
{
	GLfloat scaling[4][4] =
	{
		{ vec.getX(), 0.0f, 0.0f, 0.0f },
		{ 0.0f, vec.getY(), 0.0f, 0.0f },
		{ 0.0f, 0.0f, vec.getZ(), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	GLfloat cur_matrix[4] = { x, y, z, 1.0f };
	GLfloat result[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	for (int i = 0; i < 4; i++)
		for (int k = 0; k < 4; k++)
			result[i] = result[i] + scaling[i][k] * cur_matrix[k];

	x = result[0];
	y = result[1];
	z = result[2];
}