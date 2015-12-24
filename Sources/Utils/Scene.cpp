#include "Scene.h"
#include "..\\CImg.h"

GLuint road, grass;

void loadTexture(char* file, GLuint& texture)
{
	cimg_library::CImg<unsigned char> image(file);

	image.sRGBtoRGB();

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
	glGenerateMipmap(GL_TEXTURE_2D);
}

Scene::Scene()
{
	car = new Car(Color(0.39f, 0.0f, 0.19f, 1.0f), Vector(0.0f, 0.8f, -11.0f), 1.0f, 1.0f, 2.0f);
	car_2 = new Car(Color(0.39f, 0.5f, 0.19f, 1.0f), Vector(0.0f, 0.8f, -30.0f), 1.0f, 1.0f, 2.0f);
	sun = new Sphere(Vector(sun_x, sun_height, -far_plane), 50.0f, Color::getColor(WHITE));
	skyCube = new Cube(Color(0.59f, 0.79f, 0.98f, 1.0f), Vector(0.0f, 0.0f, 0.0f), 2 * far_plane, 2 * far_side, 2 * far_plane, false);

	AIcars.push_back(car_2);

	objects.push_back(sun);
	objects.push_back(skyCube);

	loadTexture("road.jpg", road);
	loadTexture("grass.jpg", grass);
}

void Scene::ground()
{
	GLfloat x1 = -far_side, x2 = far_side, y = 0.0f, z, z1, z2, amount;
	GLfloat texC = far_plane;
	// Base ground
	z1 = far_plane;
	z2 = -far_plane;
	glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D, grass); glBegin(GL_QUAD_STRIP);
		glTexCoord2d(0, 0); glVertex3f(x1, y, z1);
		glTexCoord2d(texC, 0); glVertex3f(x2, y, z1);
		glTexCoord2d(0, texC); glVertex3f(x1, y, z2);
		glTexCoord2d(texC, texC); glVertex3f(x2, y, z2);
	glEnd(); glDisable(GL_TEXTURE_2D);

	x1 = -2.50f, x2 = 2.50f, y = 0.01f, amount = -1.0f, texC = -0.5f;
	// Road
	glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D, road); glBegin(GL_QUAD_STRIP);
	for (z = 0.0f; z > -far_plane; z += amount)
	{
		glTexCoord2d(0, 0); glVertex3f(x1, y, z);
		glTexCoord2d(texC, 0); glVertex3f(x2, y, z);
		glTexCoord2d(0, texC); glVertex3f(x1, y, z + amount);
		glTexCoord2d(texC, texC); glVertex3f(x2, y, z + amount);
	}
	glEnd(); glDisable(GL_TEXTURE_2D);

	x1 = -0.1f, x2 = 0.1f, y = 0.011f, amount = -1.0f;
	// Discrete lines on the road
	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	for (z = 0.0f; z > -far_plane; z += amount)
	{
		if ((int)z % 2 != 0)
			continue;

		glVertex3f(x1, y, z);
		glVertex3f(x2, y, z);	
		glVertex3f(x2, y, z + amount);
		glVertex3f(x1, y, z + amount);
	}
	glEnd();
}

void Scene::draw()
{
	car->draw();

	for (auto car : AIcars)
		car->draw();

	for (auto obj : objects)
		obj->draw();

	ground();
}

void Scene::setCameraPos()
{
	static GLfloat oldZ = car->getCenter().getZ();
	GLfloat x = car->getCenter().getX(),
		y = car->getCenter().getY(),
		newZ = car->getCenter().getZ();

	//if (newZ != oldZ)
	//{
	//	sun->translate(Vector(0.0f, 0.0f, newZ - oldZ));
	//	skyCube->translate(Vector(0.0f, 0.0f, newZ - oldZ));
	//	oldZ = newZ;
	//}
	scene_cam.setEyePos(Vector(x, y + 2.0f, newZ + 7.0f));
	scene_cam.setCenter(car->getCenter());
	scene_cam.setTilt(Vector(0.0f, 1.0f, 0.0f));

	scene_cam.move(0.0f, 0.0f, 0.0f);
}

void Scene::move()
{
	car->move();
	if (car->getCenter().getZ() < -far_plane) glutExit(); // game ending
	moveAIcars();
	setCameraPos();
}

void Scene::moveAIcars()
{

}

void Scene::keyHandler()
{
	if (keys[(int)'h']) glutExit();

	if (keys[(int)'w']) car->accelerate();
	else car->decelerate(false);

	if (keys[(int)'s'])
	{
		car->decelerate(true);

		if (car->getVelocity() == 0.0f) car->move(Vector(0, 0, 0.05));
	}

	if (keys[(int)'a']) car->turn(left);

	if (keys[(int)'d']) car->turn(right);

	move();

	if (keys[(int)'q'])
		scene_cam.lookThroughMe(
			Vector(
				scene_cam.getEyePos().getX() - 5.0f,
				scene_cam.getEyePos().getY(),
				scene_cam.getEyePos().getZ() - 7.0f
				)
			);

	if (keys[(int)'e'])
		scene_cam.lookThroughMe(
			Vector(
				scene_cam.getEyePos().getX() + 5.0f,
				scene_cam.getEyePos().getY(),
				scene_cam.getEyePos().getZ() - 7.0f
				)
			);
}