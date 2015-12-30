#include "Fire.h"

#include "../CImg.h"

#include <stdlib.h>

#define fire_level 512

static GLfloat yr[fire_level];
static unsigned char fireImage[256][256][4];

void populate()
{
	for (int i = 0; i < fire_level; i++)
	{
		yr[i] = 0.1 * (rand() % 10 + 3);
	}
}

static void loadFire(char* file, GLuint& texture)
{
	static bool initiated = false;

	if (initiated) return;
	populate();
	cimg_library::CImg<unsigned char> image(file);

	//image.resize(512, 512);
	//image.sRGBtoRGB();

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());

	initiated = true;
}

Fire::Fire(Vector center)
{
	this->center = center;
	index = 0;

	Vector vec(center.getX() + 0.5f, center.getY(), center.getZ() - 0.5f);

	woods[0] = new Cube(Color::getColor(BROWN), center, 0.2f, 0.2f, 1.0f, false);
	woods[1] = new Cube(Color::getColor(BROWN), center, 0.2f, 0.2f, 1.0f, false);

	woods[0]->translate(center.negative());
	woods[0]->rotate(30.0f, 0, 1, 0);
	woods[0]->translate(center);
	woods[1]->translate(center.negative());
	woods[1]->rotate(-30.0f, 0, 1, 0);
	woods[1]->translate(center);

	populateFireImage();
	loadFireTexture();

	//loadFire("fire2.jpg", fire);
}

float noise1(int x, int y)
{
	int n;
	n = x + y * 57;
	x = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);

}

float interpol(float a, float b, float x)
{
	float ft, f;
	ft = x * 3.1415927;
	f = (1 - cos(ft)) * .5;
	return  a*(1 - f) + b*f;
}

float SmoothedNoise1(float x, float y)
{
	float corners, sides, center;
	corners = (noise1(x - 1, y - 1) + noise1(x + 1, y - 1) + noise1(x - 1, y + 1) + noise1(x + 1, y + 1)) / 16;
	sides = (noise1(x - 1, y) + noise1(x + 1, y) + noise1(x, y - 1) + noise1(x, y + 1)) / 8;
	center = noise1(x, y) / 4;
	return corners + sides + center;
}

float interpolatedNoise(float x, float y)
{
	float fractional_X, fractional_Y, v1, v2, v3, v4, i1, i2;
	int integer_X, integer_Y;

	integer_X = (int)x;
	fractional_X = x - integer_X;

	integer_Y = (int)y;
	fractional_Y = y - integer_Y;

	v1 = SmoothedNoise1(integer_X, integer_Y);
	v2 = SmoothedNoise1(integer_X + 1, integer_Y);
	v3 = SmoothedNoise1(integer_X, integer_Y + 1);
	v4 = SmoothedNoise1(integer_X + 1, integer_Y + 1);

	i1 = interpol(v1, v2, fractional_X);
	i2 = interpol(v3, v4, fractional_X);

	return interpol(i1, i2, fractional_Y);

}

float perlin(float x, float y)
{
	float total, p, frequency, amplitude;
	int i, n;
	total = 0.0;
	p = 1.0;
	n = 8;


	for (i = 0; i <= n;i++)
	{
		frequency = powf(2.0, (float)i);
		amplitude = p / (pow(2, i));
		total = total + interpolatedNoise(x*frequency / 20, y*frequency / 20)*amplitude;
	}
	return total;
}

bool makeEmpty(int i, int j)
{
	if (i < 256 / 20) return true; // upper rows of image

	if ((j < 256 / 15 && i < 200) || (j > 256 - 256 / 15 && i < 200)) return true; // left part and right part of image, except below

	return false;
}

void Fire::populateFireImage()
{
	static bool populated = false;

	if (populated) return; // populate once, use for every fire

	GLfloat flo;
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			if (rand() % 10 == 1)
			{ 
				fireImage[i][j][0] = 0;
				fireImage[i][j][1] = 0;
				fireImage[i][j][2] = 50;
				fireImage[i][j][3] = 125;
			}
			else
			{
				//flo = perlin(i, j) * 10000;
				//flo = flo / 4;

				fireImage[i][j][0] = rand() % 100 + 155;//(unsigned char)flo;
				fireImage[i][j][1] = rand() % 80;//(unsigned char)flo / 20;
				fireImage[i][j][2] = rand() % 80;//(unsigned char)flo / 20;
				fireImage[i][j][3] = rand() % 256;
			}
		}
	}
	populated = true;
}

void Fire::loadFireTexture()
{
	glGenTextures(1, &fire);
	glBindTexture(GL_TEXTURE_2D, fire);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, fireImage);
}

void Fire::draw()
{
	GLfloat x = center.getX() - 0.4f,
		y = center.getY(),
		z = center.getZ();
	GLfloat d = 0.03f;
	GLfloat texel = 1.f / 3.f;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_LIGHT0); glDisable(GL_DEPTH);
	glEnable(GL_LIGHT1);

	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { x, y, z, 1.0f };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);

	//glColor4f(1.f, 1.0f, 1.0f, 1.0f);
	

	for (int i = 0; i < fire_level; i++)
	{
		glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(yr[i], yr[i], yr[i]);
		glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D, fire);
		glBegin(GL_QUADS);
		glColor4f(1.f, 0.f, 0.f, 0.3f);
			glTexCoord2f(texel, 0.0f);    glVertex3f(1.0f, 0.0f, d);
			glTexCoord2f(texel, texel);    glVertex3f(1.0f, 1.0f, d);
			glTexCoord2f(0.0f, texel);    glVertex3f(0.0f, 1.0f, d);
			glTexCoord2f(0.0f, 0.0f);    glVertex3f(0.0f, 0.0f, d);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		if (i % 5 == 0) d = -d;
			d += 0.03f;

		yr[i] += 0.15f * i / 100.0f;

		if (yr[i] > 0.75f)
			yr[i] = 0.0f;
	}

	glDisable(GL_BLEND); glEnable(GL_LIGHT0); glDisable(GL_LIGHT1); glEnable(GL_DEPTH);
	woods[0]->draw();
	woods[1]->draw();
}