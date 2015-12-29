#include "Cube.h"

Cube::Cube() {}

Cube::Cube(Color clr, Vector center, GLfloat h, GLfloat w, GLfloat d, bool is_bn_bx) : center(center)
{
	color = clr;
	height = h;
	width = w;
	depth = d;
	top = center.getX() + width / 2;
	right = center.getY() + height / 2;
	front = center.getZ() + depth / 2;
	is_bounding_box = is_bn_bx;

	points[0] = Vector(top, right, front - depth);
	points[1] = Vector(top - width, right, front - depth);
	points[2] = Vector(top - width, right, front);
	points[3] = Vector(top, right, front);
	points[4] = Vector(top, right - height, front - depth);
	points[5] = Vector(top - width, right - height, front - depth);
	points[6] = Vector(top - width, right - height, front);
	points[7] = Vector(top, right - height, front);

	normals[0] = Vector(0.0f, 1.0f, 0.0f);
	normals[1] = Vector(0.0f, -1.0f, 0.0f);
	normals[2] = Vector(0.0f, 0.0f, 1.0f);
	normals[3] = Vector(0.0f, 0.0f, -1.0f);
	normals[4] = Vector(-1.0f, 0.0f, 0.0f);
	normals[5] = Vector(1.0f, 0.0f, 0.0f);
}

Cube::~Cube() {}

void Cube::draw()
{
	if (is_bounding_box) return;
	glPushMatrix();

	glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());

	glBegin(GL_QUADS);
		
	glNormal3f(normals[0].getX(), normals[0].getY(), normals[0].getZ()); // TOP
	glVertex3f(points[0].getX(), points[0].getY(), points[0].getZ()); // right top
	glVertex3f(points[1].getX(), points[1].getY(), points[1].getZ()); // left top
	glVertex3f(points[2].getX(), points[2].getY(), points[2].getZ()); // left bot
	glVertex3f(points[3].getX(), points[3].getY(), points[3].getZ()); // right bot

	glNormal3f(normals[1].getX(), normals[1].getY(), normals[1].getZ()); // BOT
	glVertex3f(points[4].getX(), points[4].getY(), points[4].getZ()); // right top
	glVertex3f(points[5].getX(), points[5].getY(), points[5].getZ()); // left top
	glVertex3f(points[6].getX(), points[6].getY(), points[6].getZ()); // left bot
	glVertex3f(points[7].getX(), points[7].getY(), points[7].getZ()); // right bot

	glNormal3f(normals[2].getX(), normals[2].getY(), normals[2].getZ()); // FRONT
	glVertex3f(points[3].getX(), points[3].getY(), points[3].getZ()); // right top
	glVertex3f(points[2].getX(), points[2].getY(), points[2].getZ()); // left top
	glVertex3f(points[6].getX(), points[6].getY(), points[6].getZ()); // left bot
	glVertex3f(points[7].getX(), points[7].getY(), points[7].getZ()); // right bot
	
	glNormal3f(normals[3].getX(), normals[3].getY(), normals[3].getZ()); // BACK
	glVertex3f(points[4].getX(), points[4].getY(), points[4].getZ()); // right top
	glVertex3f(points[5].getX(), points[5].getY(), points[5].getZ()); // left top
	glVertex3f(points[1].getX(), points[1].getY(), points[1].getZ()); // left bot
	glVertex3f(points[0].getX(), points[0].getY(), points[0].getZ()); // right bot

	glNormal3f(normals[4].getX(), normals[4].getY(), normals[4].getZ()); // LEFT
	glVertex3f(points[2].getX(), points[2].getY(), points[2].getZ()); // right top
	glVertex3f(points[1].getX(), points[1].getY(), points[1].getZ()); // left top
	glVertex3f(points[5].getX(), points[5].getY(), points[5].getZ()); // left bot
	glVertex3f(points[6].getX(), points[6].getY(), points[6].getZ()); // right bot

	glNormal3f(normals[5].getX(), normals[5].getY(), normals[5].getZ()); // RIGHT
	glVertex3f(points[0].getX(), points[0].getY(), points[0].getZ()); // right top
	glVertex3f(points[3].getX(), points[3].getY(), points[3].getZ()); // left top
	glVertex3f(points[7].getX(), points[7].getY(), points[7].getZ()); // left bot
	glVertex3f(points[4].getX(), points[4].getY(), points[4].getZ()); // right bot

	glEnd();

	glPopMatrix();

}

void Cube::translate(Vector translation_vec)
{
	for (int i = 0; i < 8; i++)
		points[i].translate(translation_vec);

	center.translate(translation_vec);
}

void Cube::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	for (int i = 0; i < 8; i++)
		points[i].rotate(angle, x, y, z);

	// top and bot will always have the same normal
	for (int i = 2; i < 6; i++)
		normals[i].rotate(angle, x, y, z);

	center.rotate(angle, x, y, z);
}