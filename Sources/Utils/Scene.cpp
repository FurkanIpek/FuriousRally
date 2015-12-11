#include "Scene.h"

GLfloat Points()
{
	static GLfloat road[10] = { -1.80f, -2.2f, -1.80f, -1.40f, -1.0f, -1.0f, -1.40f, -1.80f, -2.2f, -1.80f };
	static int ptr = 0;
	ptr = ptr % 10;
	return road[ptr++];
}

Scene::Scene()
{
	car = new Car(Color(0.39f, 0.0f, 0.19f, 1.0f), Vector(0.0f, 0.8f, -11.0f), 1.0f, 1.0f, 2.0f);
	car_2 = new Car(Color(0.39f, 0.5f, 0.19f, 1.0f), Vector(0.0f, 0.8f, -30.0f), 1.0f, 1.0f, 2.0f);
	sun = new Sphere(Vector(sun_x, sun_height, -far_plane), 50.0f, Color::getColor(WHITE));
	skyCube = new Cube(Color(0.59f, 0.79f, 0.98f, 1.0f), Vector(0.0f, 0.0f, 0.0f), 2 * far_plane, 2 * far_plane, 2 * far_plane, false, true);

	AIcars.push_back(car_2);

	objects.push_back(sun);
	objects.push_back(skyCube);
}

void Scene::ground()
{
	GLfloat x1 = -far_plane, x2 = far_plane, y = 0.0f, z, z1, z2;
	GLfloat amount = -far_plane;
	// Base ground
	glBegin(GL_QUAD_STRIP);
	glColor4f(0.64, 0.80, 0.50, 1.0f);
	z1 = car->getCenter().getZ() + far_plane;
	z2 = car->getCenter().getZ() - far_plane;
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x1, y, z1);
	glVertex3f(x1, y, z2);
	glVertex3f(x2, y, z1);
	glVertex3f(x2, y, z2);
	glEnd();

	x1 = -1.80f, x2 = 1.80f, y = 0.01f, amount = -1.0f;
	// Road
	glBegin(GL_QUAD_STRIP);
	glColor4f(0.75f, 0.75f, 0.75f, 0.5f);
	for (z = 0.0f; z > -far_plane; z += amount)
	{
		x1 = (Points() + x1) / 2;
		x2 = x1 + 3.60f;
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(x1, y, z);
		glVertex3f(x1, y, z + amount);
		glVertex3f(x2, y, z);
		glVertex3f(x2, y, z + amount);
	}
	glEnd();

	x1 = -0.1f, x2 = 0.1f, y = 0.011f, amount = -1.0f;
	// Discrete lines on the road
	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	for (z = 0.0f; z > -far_plane; z += amount)
	{
		if ((int)z % 2 != 0)
			continue;

		glVertex3f(x1, y, z);
		glVertex3f(x1, y, z + amount);
		glVertex3f(x2, y, z);
		glVertex3f(x2, y, z + amount);
	}
	glEnd();
}

void Scene::keyHandler()
{
	if (keys[(int)'h'])
		glutExit();

	if (keys[(int)'w'])
	{
		car->accelerate();
	}
	if (keys[(int)'w'] == false)
	{
		car->decelerate(false);
	}
	if (keys[(int)'s'])
	{
		car->decelerate(true);

		if (car->getVelocity() == 0.0f)
			car->move(Vector(0, 0, 0.05));
	}
	if (keys[(int)'a'])
	{
		car->turn(right);
	}
	if (keys[(int)'d'])
	{
		car->turn(left);
	}
	
	car->move();
	setCameraPos();

	if (keys[(int)'q'])
	{
		scene_cam.lookThroughMe(
			Vector(
				scene_cam.getEyePos().getX() - 5.0f,
				scene_cam.getEyePos().getY(),
				scene_cam.getEyePos().getZ() - 7.0f
				)
			);
	}
	if (keys[(int)'e'])
	{
		scene_cam.lookThroughMe(
			Vector(
				scene_cam.getEyePos().getX() + 5.0f,
				scene_cam.getEyePos().getY(),
				scene_cam.getEyePos().getZ() - 7.0f
				)
			);
	}
}