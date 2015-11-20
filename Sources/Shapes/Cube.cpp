#include "Cube.h"

Cube::Cube() {}

Cube::Cube(Color c, Vector v, GLfloat h, GLfloat w, GLfloat d, bool is_bn_bx)
{
	color = c;
	top = v.getX();
	right = v.getY();
	front = v.getZ();
	height = h;
	width = w;
	depth = d;
	is_bounding_box = is_bn_bx;
}

Cube::~Cube() {}

void Cube::draw()
{
	if (is_bounding_box)
		glColorMask(false, false, false, false);
	
	static GLfloat angle = 0;

	glPushMatrix();

	glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
	glTranslatef(top, right, front);
	glRotatef(angle, 0.5f, 0.5f, 0.0f);
	glBegin(GL_QUADS);
		glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
		glVertex3f(1.0f, 1.0f, -1.0f);	// Top Right Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, -1.0f);	// Top Left Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Top)
		glVertex3f(1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Top)
		glColor3f(1.0f, 0.5f, 0.0f);	// Color Orange
		glVertex3f(1.0f, -1.0f, 1.0f);	// Top Right Of The Quad (Bottom)
		glVertex3f(-1.0f, -1.0f, 1.0f);	// Top Left Of The Quad (Bottom)
		glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Quad (Bottom)
		glVertex3f(1.0f, -1.0f, -1.0f);	// Bottom Right Of The Quad (Bottom)
		glColor3f(1.0f, 0.0f, 0.0f);	// Color Red	
		glVertex3f(1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Front)
		glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Front)
		glVertex3f(-1.0f, -1.0f, 1.0f);	// Bottom Left Of The Quad (Front)
		glVertex3f(1.0f, -1.0f, 1.0f);	// Bottom Right Of The Quad (Front)
		glColor3f(1.0f, 1.0f, 0.0f);	// Color Yellow
		glVertex3f(1.0f, -1.0f, -1.0f);	// Top Right Of The Quad (Back)
		glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Left Of The Quad (Back)
		glVertex3f(-1.0f, 1.0f, -1.0f);	// Bottom Left Of The Quad (Back)
		glVertex3f(1.0f, 1.0f, -1.0f);	// Bottom Right Of The Quad (Back)
		glColor3f(0.0f, 0.0f, 1.0f);	// Color Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Left)
		glVertex3f(-1.0f, 1.0f, -1.0f);	// Top Left Of The Quad (Left)
		glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Quad (Left)
		glVertex3f(-1.0f, -1.0f, 1.0f);	// Bottom Right Of The Quad (Left)
		glColor3f(1.0f, 0.0f, 1.0f);	// Color Violet
		glVertex3f(1.0f, 1.0f, -1.0f);	// Top Right Of The Quad (Right)
		glVertex3f(1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Right)
		glVertex3f(1.0f, -1.0f, 1.0f);	// Bottom Left Of The Quad (Right)
		glVertex3f(1.0f, -1.0f, -1.0f);	// Bottom Right Of The Quad (Right)
	glEnd();

	glPopMatrix();

	angle += 0.9f;
	
	if (is_bounding_box)
		glColorMask(true, true, true, true);
}

void Cube::move(GLfloat xv, GLfloat yv, GLfloat zv)
{
	top += xv;
	right += yv;
	front += zv;
}