#include "Scene.h"
#include "..\\CImg.h"

#include <cstdlib>

GLuint road, grass, brick, finito;
char* message; // to be printed to screen

void loadTexture(char* file, GLuint& texture)
{
	cimg_library::CImg<unsigned char> image(file);

	image.sRGBtoRGB();
	image.resize(1024, 1024);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
	glGenerateMipmap(GL_TEXTURE_2D);
}

void printGL(int x, int y, int z, char *string)
{
	//set the position of the text in the window using the x and y coordinates
	glRasterPos3f(x, y, z);
	//get the length of the string to display
	int len = (int)strlen(string);

	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

GLfloat getRoadY(GLfloat z)
{
	if (z > -25.0f || z < -55.0f) return 0.01f;

	GLfloat angle, y = 0.01f;

	angle = (180.0f / 600.0f) * (-25.0f - z) / 0.05f;
	y += sin(angle * PI / 180);

	return y;
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
	GLfloat high_shininess[] = { 100.0f };

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_BLEND_SRC);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glEnable(GL_POLYGON_SMOOTH);

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
	return !(depth > -100.0f) && !(depth < -350.0f);
}

GLfloat Scene::getBezierPoint(GLfloat depth)
{
	GLfloat xa, xb, x;
	
	if (bezier(x1, x2, x3, depth))
	{
		xa = getPt(x1, x2, depth);
		xb = getPt(x2, x3, depth);

		x = getPt(xa, xb, depth);

		return x;
	}
	else
	{
		if (depth > -100.0f) return -2.50f;
		if (depth < -350.0f) return -64.07f;
	}
}

Scene::Scene()
{
	car = new Car(Color(0.39f, 0.0f, 0.19f, 1.0f), Vector(0.0f, 0.8f, -11.0f), 1.0f, 1.0f, 2.0f, true);
	//car = new Car(Color(0.39f, 0.0f, 0.19f, 1.0f), Vector(getBezierPoint(-500.f), 0.8f, -500.0f), 1.0f, 1.0f, 2.0f, true);
	Car* ai_1 = new Car(Color(0.39f, 0.5f, 0.19f, 1.0f), Vector(-1.0f, 0.8f, -15.0f), 1.0f, 1.0f, 2.0f);
	Car* ai_2 = new Car(Color(0.51f, 0.27f, 0.60f, 1.0f), Vector(1.0f, 0.8f, -15.0f), 1.0f, 1.0f, 2.0f);
	Sphere* moon = new Sphere(Vector(sun_x, sun_height, -far_plane / 2), 25.0f, Color::getColor(WHITE));
	Cube* skyCube = new Cube(Color(0.59f, 0.79f, 0.98f, 1.0f), Vector(0.0f, 0.8f, -11.0f), 500.f, 500.0f, far_plane, false);
	Fire *fire;

	fire = new Fire(Vector(getBezierPoint(-30.0f) - 1.0f, 0.0f, -30.0f));
	fires.push_back(fire);
	fire = new Fire(Vector(getBezierPoint(-30.0f) + 6.0f, 0.0f, -30.0f));
	fires.push_back(fire);
	fire = new Fire(Vector(getBezierPoint(-500.0f) - 1.0f, 0.0f, -500.0f));
	fires.push_back(fire);
	fire = new Fire(Vector(getBezierPoint(-500.0f) + 6.0f, 0.0f, -500.0f));
	fires.push_back(fire);

	treasureBox = nullptr;

	AIcars.push_back(ai_1);
	AIcars.push_back(ai_2);

	car->setSpeedLimit(speed_lim);
	for (auto aicar : AIcars)
	{
		aicar->setAngle(turnAngle / 2);
		aicar->setSpeedLimit(AI_speed_lim);
	}

	objects.push_back(moon);
	objects.push_back(skyCube);

	loadTexture("road.jpg", road);
	//loadTexture("grass.jpg", grass);
	loadTexture("finito.jpg", finito);
	loadTexture("brick.jpg", brick);

	message = "";
	cheatMode = false;

	InitEnvironment();
}

void finitoLine()
{
	GLfloat texel = 1.f / 3.f;
	glPushMatrix();
	glTranslatef(-67.0f, 0.012f, -512.0f);
	//glTranslatef(-1.0f, 1.0f, -30.0f);
	glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D, finito); glBegin(GL_QUADS);
		glColor4f(0.1f, 0.1f, 0.1f, 0.5f);
		glTexCoord2f(0.0f, 0.0f);    glVertex3f(0.0f, 0.0f, 10.0f);
		glTexCoord2f(0.0f, texel);    glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(texel, texel);    glVertex3f(10.0f, 0.0f, 0.0f);
		glTexCoord2f(texel, 0.0f);    glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd(); glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Scene::ground()
{
	GLfloat x1 = -far_side, x2 = far_side, y = 0.0f, z, z1, z2, amount;
	GLfloat texC = sqrt(far_plane);
	// Base ground
	z1 = far_plane;
	z2 = -far_plane;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D, road); glBegin(GL_QUADS);
		glColor4f(0.19f, 0.19f, 0.19f, 1.0f);
		glTexCoord2d(0, 0); glVertex3f(x1, y, z1);
		glTexCoord2d(0, texC); glVertex3f(x1, y, z2);
		glTexCoord2d(texC, texC); glVertex3f(x2, y, z2);
		glTexCoord2d(texC, 0); glVertex3f(x2, y, z1);
	glEnd(); glDisable(GL_TEXTURE_2D);

	x1 = -2.50f, x2 = 2.50f, y = 0.01f, amount = -0.05f, texC = -0.5f;
	GLfloat angle = 0.0f;
	// Road
	glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D, road); glBegin(GL_QUAD_STRIP);
	for (z = 0.0f; z > -far_plane/2; z += amount)
	{
		x1 = getBezierPoint(z); x2 = x1 + 5.0f;
		y = 0.01f;
		if (z < -25.0f && z > -55.0f)
		{
			angle += 180.0f / 600.0f;
			y += sin(angle * PI / 180);
		}

		glColor3f(0.19f, 0.19f, 0.19f);
		glTexCoord2d(0, 0); glVertex3f(x1, y, z);
		glTexCoord2d(texC, 0); glVertex3f(x2, y, z);
		glTexCoord2d(0, texC); glVertex3f(x1, y, z + amount);
		glTexCoord2d(texC, texC); glVertex3f(x2, y, z + amount);
	}
	glEnd(); glDisable(GL_TEXTURE_2D); glDisable(GL_BLEND);

	x1 = -2.50f, y = 0.011f, angle = 0.0f;
	// Discrete lines on the road
	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	for (z = 0.0f; z > -far_plane/2; z += amount)
	{
		x1 = getBezierPoint(z); x2 = x1 + 0.2f;

		y = 0.011f;
		if (z < -25.0f && z > -55.0f)
		{
			angle += 180.0f / 600.0f;
			y += sin(angle * PI / 180);
		}

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
	GLfloat point = -(rand() % 15) - 15.0f;
	Vector vec(getBezierPoint(car_z - 20.0f) + 2.5f, getRoadY(car_z + point) + 1.0f, car_z + point);

	if (treasureBox != nullptr) delete(treasureBox);

	treasureBox = new Cube(Color::getColor(WHITE), vec, 1.0f, 1.0f, 1.0f);
	treasureBox->prizeBox(brick);
}

void Scene::portForward(Car* car)
{
	GLfloat zet = car->getCenter().getZ();
	Vector vec(getBezierPoint(zet) + 2.50f, getRoadY(zet), zet - 7.5f);
	
	car->move(car->getCenter().negative());
	car->move(vec);
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
	printGL(car->getCenter().getX(), 2.0f, car->getCenter().getZ() - 20.0f, message);

	if (cheatMode)
	{
		glLoadIdentity();
		//glTranslatef(car->getCenter().getX(), 2.0f, car->getCenter().getZ() - 20.0f);
		glTranslatef(trX, 0.f, 0.f);
		glTranslatef(0.f, trY, 0.f);
		glTranslatef(0.f, 0.f, zoom);
		glRotatef(rotation * 2, 0.f, 0.5f, 0.f);
	}

	int r = rand() % 200;
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

	for (auto fire : fires)
		fire->draw();

	ground();
	finitoLine();
}

void Scene::setCameraPos()
{
	static GLfloat oldZ = -11.0f, oldX = 1.0f;
	GLfloat x = car->getCenter().getX(),
		y = car->getCenter().getY(),
		z = car->getCenter().getZ(),
		diffX = x - oldX,
		diffZ = z - oldZ;

	oldZ = z;
	oldX = x;
	Vector vec(0.f, 0.f, diffZ);
	
	for (auto obj : objects)
		obj->translate(vec);

	Camera::instance().setEyePos(car->getCenter());
	Camera::instance().setCenter(car->getCenter());
	Camera::instance().setTilt(Vector(0.0f, 1.0f, 0.0f));
	Camera::instance().lookThroughMe();
}

void Scene::outOfRoadCheck(Car* car)
{
	GLfloat car_x = car->getCenter().getX();
	GLfloat bezier_x = getBezierPoint(car->getCenter().getZ());

	if (car_x < bezier_x || car_x > bezier_x + 5.0f)
	{
		if (car->getVelocity() > car->getSpeedLimit() / 3)
			car->setVelocity(car->getVelocity() - 0.1f);
	}
}

void Scene::roadHeight(Car* car)
{
	Vector car_center = car->getCenter();
	GLfloat car_z = car_center.getZ();
	GLfloat bezier = getBezierPoint(car_z);

	if (car_z > bezier - 2.5f || car_z < bezier + 2.5f)
	{
		GLfloat res = getRoadY(car_z);
		GLfloat diff = res - car_center.getY() + 0.8f + 0.1f;

		if (diff != 0.0f && abs(bezier - car_center.getX()) <= 5.0f)
		{
			//car->rotate(1.0f, diff, 0.0f, 0.0f);
			car->move(Vector(0.0f, diff, 0.0f));
		}
	}
}

static void arabulucu(int val)
{
	Scene::getInstance().onClose(val);
}

void Scene::isCarReachedFinishLine(Car* c_car)
{
	Vector vec = c_car->getCenter();
	GLfloat car_x = vec.getX(), car_z = vec.getZ(),
		bezier_x = getBezierPoint(car_z);

	if (abs(bezier_x - car_x) < 5.0f && car_z <= -far_plane / 2)
	{
		if (c_car->carIsUser())
			message = "YOU WIN!";
		else
			message = "YOU LOSE!";

		car->setVelocity(0);
		car->decelerate(false);

		for (auto aicar : AIcars)
		{
			aicar->setVelocity(0);
			aicar->decelerate(false);
		}

		glutTimerFunc(3000, arabulucu, 0);
	}
}

void Scene::move()
{
	car->move();
	outOfRoadCheck(car);
	roadHeight(car);
	isCarReachedFinishLine(car);

	if (car->getCenter().getZ() < -far_plane) glutExit(); // game ending

	moveAIcars();
	AIcars.at(0)->checkCollision(AIcars.at(1));

	for (auto aicar : AIcars)
	{
		car->checkCollision(aicar);
		outOfRoadCheck(aicar);
		roadHeight(aicar);
		isCarReachedFinishLine(aicar);
	}

	setCameraPos();
}

void Scene::moveAIcars()
{
	GLfloat car_x, bezier_x, forward_bezier;
	for (auto aicar : AIcars)
	{
		car_x = aicar->getCenter().getX();
		bezier_x = getBezierPoint(aicar->getCenter().getZ()) + 2.5f;
		forward_bezier = getBezierPoint(aicar->getCenter().getZ() - 10.0f) + 2.5f;

		if (abs(car_x - bezier_x) > 0.5f)
		{
			if (car_x > bezier_x + 1.5f)
			{
				aicar->decelerate(true);
				aicar->turn(left);
			}
			else if (car_x < bezier_x - 1.5f)
			{
				aicar->decelerate(true);
				aicar->turn(right);
			}
		}

		if (abs(forward_bezier - car_x) < 0.3f)
			aicar->straighten();

		if (rand() % 150 == 1) aicar->decelerate(true);
		else aicar->accelerate();

		aicar->move();
	}
}

void Scene::keyHandler()
{
	static GLfloat angle = 2.0f;
	if (keys[(int)'h']) glutExit();

	if (keys[(int)'u']) cheatMode = true;

	if (keys[(int)'y']) {
		trX = car->getCenter().getX();
		trY = car->getCenter().getY() + 5.f;
		zoom = rotation = 0.f;
		cheatMode = false;
	}

	if (cheatMode) return;

	if (keys[(int)'k']) glutFullScreen();

	if (keys[(int)'l']) glutLeaveFullScreen();

	if (keys[(int)'w']) car->accelerate();
	else car->decelerate(false);

	if (keys[(int)'s'])
		car->decelerate(true);
	
	if (keys[(int)'a']) {
		if (car->turn(left))
			Camera::instance().rotate(turnAngle);
	}

	if (keys[(int)'d']) {
		if (car->turn(right))
			Camera::instance().rotate(-turnAngle);
	}

	if (keys[(int)'r']) {
		car->straighten();
		Camera::instance().resetAngle();
	}

	move();

	if (keys[(int)'q']) {
		Camera::instance().changeView(-90.0f, 0.0f, 1.0f, 0.0f);
		Camera::instance().lookThroughMe();
	}

	if (keys[(int)'e']) {
		Camera::instance().changeView(90.0f, 0.0f, 1.0f, 0.0f);
		Camera::instance().lookThroughMe();
	}

	//if (keys[(int)'f']) {
	//	Camera::instance().changeView(90.0f, 1.0f, 0.0f, 0.0f);
	//	Camera::instance().lookThroughMe();
	//}

	InitEnvironment();
}

void close(unsigned char keyPressed, int x, int y) { glutExit(); }

void Scene::onClose(int val)
{
	glutIdleFunc(NULL);
	glutKeyboardFunc(close);
	glutKeyboardUpFunc(NULL);
	glutLeaveMainLoop();
}