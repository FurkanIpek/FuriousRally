#include "Scene.h"
#include "..\\CImg.h"

#include <cstdlib>

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

void InitEnvironment()
{
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { sun_x, sun_height, far_plane, 1.0f };

	GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat high_shininess[] = { 50.0f };

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_POLYGON_SMOOTH);

	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND_SRC);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

GLfloat getPt(GLfloat n1, GLfloat n2, GLfloat perc)
{
	GLfloat diff = n2 - n1;

	return n1 + (diff * perc/far_plane);
}

bool bezier(GLfloat& x1, GLfloat& x2, GLfloat& x3, GLfloat depth)
{
	//return (depth < -100.0f && depth > -150.0f)
	//	|| (depth < -400.0f && depth > -450.0f);

	return true;
}

GLfloat Scene::getBezierPoint(GLfloat depth)
{
	GLfloat xa, za, xb, zb, x, z;
	
	if (bezier(x1, x2, x3, depth))
	{
		//if (swap) std::swap(x1, x3);
		// The Green Line
		xa = getPt(x1, x2, depth);
		//za = getPt(z1, z2, depth);
		xb = getPt(x2, x3, depth);
		//zb = getPt(z2, z3, depth);

		// The Black Dot
		x = getPt(xa, xb, depth);
		//z = getPt(za, zb, depth);
		if (depth < 150.0f && depth > 150.5f) printf("%i\n", x);
	}
	else
	{
		if (depth > -100.0f) return -2.50f;
		if (depth < -150.0f && depth > -400.0f) return -13.0f;
		if (depth < -450.0f) return -15.0f;
	}

	return x;
}

Scene::Scene()
{
	car = new Car(Color(0.39f, 0.0f, 0.19f, 1.0f), Vector(1.0f, 0.8f, -11.0f), 1.0f, 1.0f, 2.0f);
	Car* ai_1 = new Car(Color(0.39f, 0.5f, 0.19f, 1.0f), Vector(-1.0f, 0.8f, -15.0f), 1.0f, 1.0f, 2.0f);
	Car* ai_2 = new Car(Color(0.51f, 0.27f, 0.60f, 1.0f), Vector(1.0f, 0.8f, -15.0f), 1.0f, 1.0f, 2.0f);
	sun = new Sphere(Vector(sun_x, sun_height, -far_plane), 50.0f, Color::getColor(WHITE));
	skyCube = new Cube(Color(0.59f, 0.79f, 0.98f, 1.0f), Vector(0.0f, 0.0f, 0.0f), 2 * far_plane, 2 * far_side, 2 * far_plane, false);
	treasureBox = nullptr;

	AIcars.push_back(ai_1);
	AIcars.push_back(ai_2);

	car->setSpeedLimit(speed_lim);
	for (auto car : AIcars) car->setSpeedLimit(AI_speed_lim);

	objects.push_back(sun);
	objects.push_back(skyCube);
	createTreasureBox();
	loadTexture("road.jpg", road);
	loadTexture("grass.jpg", grass);

	InitEnvironment();
}

void Scene::ground()
{
	GLfloat x1 = -far_side, x2 = far_side, y = 0.0f, z, z1, z2, amount;
	GLfloat texC = far_plane;
	// Base ground
	z1 = far_plane;
	z2 = -far_plane;
	glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D, road); glBegin(GL_QUAD_STRIP);
		glTexCoord2d(0, 0); glVertex3f(x1, y, z1);
		glTexCoord2d(texC, 0); glVertex3f(x2, y, z1);
		glTexCoord2d(0, texC); glVertex3f(x1, y, z2);
		glTexCoord2d(texC, texC); glVertex3f(x2, y, z2);
	glEnd(); glDisable(GL_TEXTURE_2D);

	x1 = -2.50f, x2 = 2.50f, y = 0.01f, amount = -0.05f, texC = -0.5f;
	// Road
	/*glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D, road);*/ glBegin(GL_QUAD_STRIP);
	for (z = 0.0f; z > -far_plane; z += amount)
	{
		x1 = getBezierPoint(z); x2 = x1 + 5.0f;

		glColor3f(0.19f, 0.19f, 0.19f);
		glTexCoord2d(0, 0); glVertex3f(x1, y, z);
		glTexCoord2d(texC, 0); glVertex3f(x2, y, z);
		glTexCoord2d(0, texC); glVertex3f(x1, y, z + amount);
		glTexCoord2d(texC, texC); glVertex3f(x2, y, z + amount);
	}
	glEnd(); glDisable(GL_TEXTURE_2D);

	x1 = -2.50f, y = 0.011f;
	// Discrete lines on the road
	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	for (z = 0.0f; z > -far_plane; z += amount)
	{
		x1 = getBezierPoint(z); x2 = x1 + 0.2f;

		if ((int)z % 2 != 0)
			continue;
		
		glVertex3f(x1 + 2.50f, y, z);
		glVertex3f(x2 + 2.50f, y, z);
		glVertex3f(x2 + 2.50f, y, z + amount);
		glVertex3f(x1 + 2.50f, y, z + amount);
	}
	glEnd();
}

void Scene::createTreasureBox()
{
	GLfloat car_z = car->getCenter().getZ();
	Vector vec(getBezierPoint(car_z - 20.0f) + 2.5f, 1.25f, car_z - 20.0f);
	if (treasureBox == nullptr)
		treasureBox = new Cube(Color::getColor(WHITE), vec, 1.0f, 1.0f, 1.0f);
	else
	{
		delete(treasureBox);
		treasureBox = new Cube(Color::getColor(WHITE), vec, 1.0f, 1.0f, 1.0f);
		//treasureBox->visibility(true);
	}
}

void Scene::portForward(Car* vehicle)
{
	Vector vec(getBezierPoint(vehicle->getCenter().getZ()), 0.8f, vehicle->getCenter().getZ() - 7.5f);
	vehicle->move(vehicle->getCenter().negative());
	vehicle->move(vec);
}

void Scene::prizeCheck()
{
	if (treasureBox != nullptr)
	{
		if (car->checkCollision(treasureBox))
		{
			portForward(car);
			delete(treasureBox); treasureBox = nullptr;
		}
		else
		{
			for (auto aicar : AIcars)
			{
				if (aicar->checkCollision(treasureBox))
				{
					portForward(aicar);
					delete(treasureBox); treasureBox = nullptr;
					break;
				}
			}
		}
	}
}

void Scene::draw()
{
	int r = rand() % 100;

	if (r == 50) createTreasureBox();

	prizeCheck();

	if (treasureBox != nullptr)
	{
		Vector cen = treasureBox->getCenter();
		treasureBox->translate(cen.negative());
		treasureBox->rotate(turnAngle, 0.0f, 1.0f, 1.0f);
		treasureBox->translate(cen);
		treasureBox->draw();
	}
	
	car->draw();

	for (auto aicar : AIcars)
		aicar->draw();

	for (auto obj : objects)
		obj->draw();

	ground();
}

void Scene::setCameraPos()
{
	static GLfloat oldZ = -11.0f;
	GLfloat x = car->getCenter().getX(),
		y = car->getCenter().getY(),
		z = car->getCenter().getZ(),
		diff = z - oldZ;

	oldZ = z;

	skyCube->translate(Vector(0.f, 0.f, diff));
	sun->translate(Vector(0.f, 0.f, diff));

	scene_cam.setEyePos(Vector(x, y + 2.0f, z + camDistance));
	scene_cam.setCenter(car->getCenter());
	scene_cam.setTilt(Vector(0.0f, 1.0f, 0.0f));

	scene_cam.move(0.0f, 0.0f, 0.0f);
}

void Scene::outOfRoadCheck(Car* car)
{
	GLfloat car_x = car->getCenter().getX();
	GLfloat bezier_x = getBezierPoint(car->getCenter().getZ());

	if (car_x < bezier_x || car_x > bezier_x + 5.0f)
		car->setVelocity(car->getVelocity() - acc);
}

void Scene::move()
{
	car->move();
	outOfRoadCheck(car);

	if (car->getCenter().getZ() < -far_plane) glutExit(); // game ending

	moveAIcars();

	for (auto aicar : AIcars)
	{
		car->checkCollision(aicar);
		outOfRoadCheck(aicar);
	}

	AIcars[0]->checkCollision(AIcars[1]);

	setCameraPos();
}

void Scene::moveAIcars()
{
	GLfloat car_x, bezier_x;
	for (auto aicar : AIcars)
	{
		car_x = aicar->getCenter().getX();
		bezier_x = getBezierPoint(aicar->getCenter().getZ()) + 2.5f;

		int idiott = rand() % 10;
		// TODO user arkada ise direksiyonu önüne kýr
		if (idiott != 9)
		{
			if (car_x > bezier_x + 1.5f)
				aicar->turn(left);
			else if (car_x < bezier_x - 1.5f)
				aicar->turn(right);
		}

		aicar->accelerate();
		aicar->move();
	}
}

void Scene::keyHandler()
{
	if (keys[(int)'h']) glutExit();

	if (keys[(int)'w']) car->accelerate();
	else car->decelerate(false);

	if (keys[(int)'s'])
		car->decelerate(true);
	
	if (keys[(int)'a']) {
		car->turn(left);
		scene_cam.rotate(turnAngle, 0, 1, 0);
	}

	if (keys[(int)'d']) {
		car->turn(right);
		scene_cam.rotate(-turnAngle, 0, 1, 0);
	}

	if (keys[(int)'r']) car->straighten();

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

	if (keys[(int)'f'])
		scene_cam.lookThroughMe(
			Vector(
				scene_cam.getEyePos().getX(),
				scene_cam.getEyePos().getY(),
				scene_cam.getEyePos().getZ() - 14.0f
				)
			);
	InitEnvironment();
}