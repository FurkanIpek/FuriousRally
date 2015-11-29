#include "Cube.h"

Cube::Cube() {}

Cube::Cube(Color clr, Vector v, GLfloat h, GLfloat w, GLfloat d, bool is_bn_bx)
{
	color = clr;
	top = v.getX();
	right = v.getY();
	front = v.getZ();
	height = h;
	width = w;
	depth = d;
	is_bounding_box = is_bn_bx;

	points[0] = Vector(top, right, front - depth);
	points[1] = Vector(top - width, right, front - depth);
	points[2] = Vector(top - width, right, front);
	points[3] = Vector(top, right, front);
	points[4] = Vector(top, right - height, front - depth);
	points[5] = Vector(top - width, right - height, front - depth);
	points[6] = Vector(top - width, right - height, front);
	points[7] = Vector(top, right - height, front);
}

Cube::~Cube() {}

void Cube::draw()
{
	glPushMatrix();

	if (is_bounding_box)
		glColorMask(false, false, false, false);

	glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());

	glBegin(GL_QUADS);
	// TOP
	glVertex3f(points[0].getX(), points[0].getY(), points[0].getZ()); // right top
	glVertex3f(points[1].getX(), points[1].getY(), points[1].getZ()); // left top
	glVertex3f(points[2].getX(), points[2].getY(), points[2].getZ()); // left bot
	glVertex3f(points[3].getX(), points[3].getY(), points[3].getZ()); // right bot

																	  // BOT
	glVertex3f(points[4].getX(), points[4].getY(), points[4].getZ()); // right top
	glVertex3f(points[5].getX(), points[5].getY(), points[5].getZ()); // left top
	glVertex3f(points[6].getX(), points[6].getY(), points[6].getZ()); // left bot
	glVertex3f(points[7].getX(), points[7].getY(), points[7].getZ()); // right bot

																	  // FRONT
	glVertex3f(points[3].getX(), points[3].getY(), points[3].getZ()); // right top
	glVertex3f(points[2].getX(), points[2].getY(), points[2].getZ()); // left top
	glVertex3f(points[6].getX(), points[6].getY(), points[6].getZ()); // left bot
	glVertex3f(points[7].getX(), points[7].getY(), points[7].getZ()); // right bot

																	  // BACK
	glVertex3f(points[4].getX(), points[4].getY(), points[4].getZ()); // right top
	glVertex3f(points[5].getX(), points[5].getY(), points[5].getZ()); // left top
	glVertex3f(points[1].getX(), points[1].getY(), points[1].getZ()); // left bot
	glVertex3f(points[0].getX(), points[0].getY(), points[0].getZ()); // right bot

																	  // LEFT
	glVertex3f(points[2].getX(), points[2].getY(), points[2].getZ()); // right top
	glVertex3f(points[1].getX(), points[1].getY(), points[1].getZ()); // left top
	glVertex3f(points[5].getX(), points[5].getY(), points[5].getZ()); // left bot
	glVertex3f(points[6].getX(), points[6].getY(), points[6].getZ()); // right bot

																	  // RIGHT
	glVertex3f(points[0].getX(), points[0].getY(), points[0].getZ()); // right top
	glVertex3f(points[3].getX(), points[3].getY(), points[3].getZ()); // left top
	glVertex3f(points[7].getX(), points[7].getY(), points[7].getZ()); // left bot
	glVertex3f(points[4].getX(), points[4].getY(), points[4].getZ()); // right bot
	glEnd();

	if (is_bounding_box)
		glColorMask(true, true, true, true);

	glPopMatrix();
}

void Cube::move(GLfloat xv, GLfloat yv, GLfloat zv)
{
	Vector translation_vec(xv, yv, zv);

	for (int i = 0; i < 8; i++)
		points[i].translate(translation_vec);
}