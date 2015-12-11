#define _SCL_SECURE_NO_WARNINGS
#include "Cube.h"
#include "..\bitmap\bitmap_image.hpp"

GLuint loadTextures(int i)
{
	static char* files[6] = { "skybox\\ascend4bk.bmp",
		"skybox\\ascend4dn.bmp", "skybox\\ascend4ft.bmp",
		"skybox\\ascend4lf.bmp", "skybox\\ascend4rt.bmp" ,
		"skybox\\ascend4up.bmp" };

	bitmap_image image(files[i]);

	int width = image.width(),
		height = image.height();

	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image.data());
	
	
	return texture;
}

Cube::Cube() {}

Cube::Cube(Color clr, Vector center, GLfloat h, GLfloat w, GLfloat d, bool is_bn_bx, bool text_map) : center(center), texture_map(text_map)
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

	if (text_map)
	{
		for (int i = 0; i < 6; i++)
			textures[i] = loadTextures(i);
	}
}

Cube::~Cube() {}

void Cube::drawSky()
{
	// TODO texture map sky doesn't work
	// TODO top, bot ve back a texture mappinge gerek yok
	glPushMatrix();

	glColor4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());

	glBegin(GL_QUADS);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glNormal3f(normals[0].getX(), normals[0].getY(), normals[0].getZ()); // TOP
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexCoord2f(1, 1);
	glVertex3f(points[0].getX(), points[0].getY(), points[0].getZ()); // right top
	glTexCoord2f(0, 1);
	glVertex3f(points[1].getX(), points[1].getY(), points[1].getZ()); // left top
	glTexCoord2f(0, 0);
	glVertex3f(points[2].getX(), points[2].getY(), points[2].getZ()); // left bot
	glTexCoord2f(1, 0);
	glVertex3f(points[3].getX(), points[3].getY(), points[3].getZ()); // right bot
	glDisable(GL_TEXTURE_2D);

	glNormal3f(normals[1].getX(), normals[1].getY(), normals[1].getZ()); // BOT
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexCoord2f(1, 1);
	glVertex3f(points[4].getX(), points[4].getY(), points[4].getZ()); // right top
	glTexCoord2f(0, 1);
	glVertex3f(points[5].getX(), points[5].getY(), points[5].getZ()); // left top
	glTexCoord2f(0, 0);
	glVertex3f(points[6].getX(), points[6].getY(), points[6].getZ()); // left bot
	glTexCoord2f(1, 0);
	glVertex3f(points[7].getX(), points[7].getY(), points[7].getZ()); // right bot
	glDisable(GL_TEXTURE_2D);

	glNormal3f(normals[2].getX(), normals[2].getY(), normals[2].getZ()); // FRONT
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexCoord2f(1, 1);
	glVertex3f(points[3].getX(), points[3].getY(), points[3].getZ()); // right top
	glTexCoord2f(0, 1);
	glVertex3f(points[2].getX(), points[2].getY(), points[2].getZ()); // left top
	glTexCoord2f(0, 0);
	glVertex3f(points[6].getX(), points[6].getY(), points[6].getZ()); // left bot
	glTexCoord2f(1, 0);
	glVertex3f(points[7].getX(), points[7].getY(), points[7].getZ()); // right bot
	glDisable(GL_TEXTURE_2D);

	glNormal3f(normals[3].getX(), normals[3].getY(), normals[3].getZ()); // BACK
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexCoord2f(1, 1);
	glVertex3f(points[4].getX(), points[4].getY(), points[4].getZ()); // right top
	glTexCoord2f(0, 1);
	glVertex3f(points[5].getX(), points[5].getY(), points[5].getZ()); // left top
	glTexCoord2f(0, 0);
	glVertex3f(points[1].getX(), points[1].getY(), points[1].getZ()); // left bot
	glTexCoord2f(1, 0);
	glVertex3f(points[0].getX(), points[0].getY(), points[0].getZ()); // right bot
	glDisable(GL_TEXTURE_2D);

	glNormal3f(normals[4].getX(), normals[4].getY(), normals[4].getZ()); // LEFT
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glTexCoord2f(1, 1);
	glVertex3f(points[2].getX(), points[2].getY(), points[2].getZ()); // right top
	glTexCoord2f(0, 1);
	glVertex3f(points[1].getX(), points[1].getY(), points[1].getZ()); // left top
	glTexCoord2f(0, 0);
	glVertex3f(points[5].getX(), points[5].getY(), points[5].getZ()); // left bot
	glTexCoord2f(1, 0);
	glVertex3f(points[6].getX(), points[6].getY(), points[6].getZ()); // right bot
	glDisable(GL_TEXTURE_2D);

	glNormal3f(normals[5].getX(), normals[5].getY(), normals[5].getZ()); // RIGHT
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glTexCoord2f(1, 1);
	glVertex3f(points[0].getX(), points[0].getY(), points[0].getZ()); // right top
	glTexCoord2f(0, 1);
	glVertex3f(points[3].getX(), points[3].getY(), points[3].getZ()); // left top
	glTexCoord2f(0, 0);
	glVertex3f(points[7].getX(), points[7].getY(), points[7].getZ()); // left bot
	glTexCoord2f(1, 0);
	glVertex3f(points[4].getX(), points[4].getY(), points[4].getZ()); // right bot

	glDisable(GL_TEXTURE_2D);
	glEnd();

	glPopMatrix();
}

void Cube::draw()
{
	if (is_bounding_box) return;
	if (texture_map)
	{
		drawSky();
		return;
	}
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

void Cube::move(GLfloat xv, GLfloat yv, GLfloat zv)
{
	Vector translation_vec(xv, yv, zv);

	for (int i = 0; i < 8; i++)
		points[i].translate(translation_vec);
}

void Cube::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	for (int i = 0; i < 8; i++)
	{
		/*points[i].setX(points[i].getX() - center.getX());
		points[i].setY(points[i].getY() - center.getY());
		points[i].setZ(points[i].getZ() - center.getZ());*/

		points[i].rotate(angle, x, y, z);

		/*points[i].setX(points[i].getX() + center.getX());
		points[i].setY(points[i].getY() + center.getY());
		points[i].setZ(points[i].getZ() + center.getZ());*/
	}
	// TODO ask about normals? when i rotate the cube, lightning of the environment goes crazy
	for (int i = 0; i < 6; i++)
	{
		normals[i].rotate(angle, x, y, z);
	}
}