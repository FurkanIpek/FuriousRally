#include "Utils\includes.h"

Car* car;
Car* car_2;
Sphere sun(Vector(sun_x, sun_height, -far_plane), 50.0f, Color::getColor(YELLOW));
Camera scene_cam;
Cube kup(Color(0.39f, 0.0f, 0.19f, 1.0f), Vector(0.0f, 0.5f, -11.0f), 1.0f, 1.0f, 2.0f);

bool keys[256] = { false };

void setCameraPos()
{
	scene_cam.setEyePos(Vector(car->getCenter().getX(), car->getCenter().getY() + 2.0f, car->getCenter().getZ() + 7.0f));
	scene_cam.setCenter(car->getCenter());
	scene_cam.setTilt(Vector(0.0f, 1.0f, 0.0f));

	scene_cam.move(0.0f, 0.0f, 0.0f);
}

static void Reshape(int width, int height)
{
	if (height <= 0)
		height = 1;

	const int aspectratio = width / height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(65.0f, aspectratio, 0.1f, far_plane);

	setCameraPos();
}

void track()
{
	GLfloat x1 = -1.80f, x2 = 1.80f, y = 0.0f, z;
	GLfloat amount = -1.0f;

	glBegin(GL_QUAD_STRIP);
	glColor4f(0.75f, 0.75f, 0.75f, 0.5f);
	for (z = 0.0f; z > -far_plane; z += amount)
	{
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(x1, y, z);
		glVertex3f(x1, y, z + amount);
		glVertex3f(x2, y, z);
		glVertex3f(x2, y, z + amount);
	}
	glEnd();

	x1 = -0.1f, x2 = 0.1f, y = 0.01f;

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

void sky(GLfloat r, GLfloat l)
{
	float x, y, z;

	glBegin(GL_QUAD_STRIP);

	glColor3f(0.59f, 0.79f, 0.98f);

	for (int d = 0; d <= 365; d++)
	{
		x = r*cos(cn*d);
		z = r*sin(cn*d);
		y = 0;
		glVertex3f(x, y, z);

		y = l;
		glVertex3f(x, y, z);
	}

	glEnd();
}

static void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.64, 0.80, 0.50, 1);

	car->draw();
	car_2->draw();
	//kup.draw();

	sky(far_plane, far_plane);
	sun.draw();
	track();

	glutSwapBuffers();
}

static void keyHandler()
{
	Vector vec(0, 0, 0);
	GLfloat magnitude = 0.05f;

	if (keys[(int)'w']) {
		vec.setZ(-magnitude);
		kup.rotate(20.0f, 1.0f, 1.0f, 0.0f);
	}
	if (keys[(int)'s']) {
		vec.setZ(magnitude);
	}
	if (keys[(int)'a']) {
		vec.setX(-magnitude);
	}
	if (keys[(int)'d']) {
		vec.setX(magnitude);
	}
	//if (car->getVelocity() >= 0.0f && keys[(int)'w'] == true)
	{
		car->move(vec.getX(), vec.getY(), vec.getZ());
		setCameraPos();
	}

	if (keys[(int)'h'])
		glutExit();

	if (keys[(int)'q']) {
		scene_cam.lookThroughMe(
			Vector(
				scene_cam.getEyePos().getX() - 5.0f,
				scene_cam.getEyePos().getY(),
				scene_cam.getEyePos().getZ() - 7.0f
				)
			);
	}
	if (keys[(int)'e']) {
		scene_cam.lookThroughMe(
			Vector(
				scene_cam.getEyePos().getX() + 5.0f,
				scene_cam.getEyePos().getY(),
				scene_cam.getEyePos().getZ() - 7.0f
				)
			);
	}
}

static void KeyRelease(unsigned char keyPressed, int x, int y)
{
	keyPressed = tolower(keyPressed);

	keys[(int)keyPressed] = false;
}

static void KeyPress(unsigned char keyPressed, int x, int y)
{
	keyPressed = tolower(keyPressed);
	keys[(int)keyPressed] = true;
}

static void Idle(void)
{
	keyHandler();
	Display();
}

void InitEnvironment()
{
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { sun_x, sun_height, -far_plane, 0.0f };

	GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat high_shininess[] = { 100.0f };
	// TODO wtf this does
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

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

int main(int argc, char* argv [])
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Furious Rally");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return EXIT_FAILURE;

	glutIdleFunc(Idle);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(KeyPress);
	glutKeyboardUpFunc(KeyRelease);
	//glutFullScreen();
	
	car = new Car(Color(0.39f, 0.0f, 0.19f, 1.0f), Vector(0.0f, 1.5f, -11.0f), 1.0f, 1.0f, 2.0f);
	car_2 = new Car(Color(0.39f, 0.5f, 0.19f, 1.0f), Vector(0.0f, 1.5f, -30.0f), 1.0f, 1.0f, 2.0f);

	InitEnvironment();
	glutMainLoop();

	return EXIT_SUCCESS;
}

// TODO use bezier curves for drawing track/road

// TODO scene graphs
// TODO add normals
// TODO robot arm örneðine bak