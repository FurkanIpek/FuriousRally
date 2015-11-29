#include "Utils\includes.h"

#define far_plane 1000.0f
#define sun_height 200.0f
#define sun_x 70.0f

Car* car;
Cylinder sky_box(Color(0.62f, 0.62f, 0.62f, 1.0f), far_plane, far_plane);
Sphere sun(Vector(sun_x, sun_height, -far_plane), 50.0f, Color::getColor("yellow"));
Camera scene_cam;

void setCameraPos()
{
	scene_cam.setEyePos(Vector(car->center.getX(), car->center.getY() + 2.0f, car->center.getZ() + 7.0f));
	scene_cam.setCenter(car->center);
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

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	setCameraPos();
}

void track()
{
	static GLfloat x1 = -1.5f, x2 = 1.5f, y = 0.0f, z;
	GLfloat amount = -0.5f, increment = 0.1f;
	int ctr;

	glBegin(GL_QUAD_STRIP);
	glColor4f(0.75f, 0.75f, 0.75f, 1.0f);
	for (z = 0.0f, ctr= 0; z > -far_plane; z += amount, ctr++)
	{
		glVertex3f(x1, y, z);
		glVertex3f(x1, y, z + amount);

		glVertex3f(x2, y, z);
		glVertex3f(x2, y, z + amount);
	}
	glEnd();
}

static void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.64, 0.80, 0.50, 1);

	car->draw();

	sky_box.draw();
	sun.draw();
	track();

	glutSwapBuffers();
}

static void Idle(void)
{
	Display();
}

static void KeyPress(unsigned char keyPressed, int x, int y)
{
	Vector vec(0, 0, 0);
	GLfloat magnitude = 0.1f;

	if (keyPressed == 'w') {
		vec.setZ(-magnitude);
	}
	if (keyPressed == 's') {
		vec.setZ(magnitude);
	}
	if (keyPressed == 'a') {
		vec.setX(-magnitude);
	}
	if (keyPressed == 'd') {
		vec.setX(magnitude);
	}
	if (keyPressed == 'q') {
		scene_cam.lookThroughMe(
			Vector(
				scene_cam.getEyePos().getX() + scene_cam.getEyePos().getZ(),
				scene_cam.getEyePos().getY(),
				scene_cam.getEyePos().getZ() - 7.0f
				)
			);
	}
	if (keyPressed == 'e') {
		scene_cam.lookThroughMe(
			Vector(
				scene_cam.getEyePos().getX() - scene_cam.getEyePos().getZ(),
				scene_cam.getEyePos().getY(),
				scene_cam.getEyePos().getZ() + 7.0f
				)
			);
	}

	car->move(vec.getX(), vec.getY(), vec.getZ());

	if (keyPressed == 'h')
		glutExit();
	
	glutPostRedisplay();
}

static void MouseFunc(int button, int state, int x, int y)
{

}

static void MotionFunc(int x, int y)
{

}

void InitEnvironment()
{
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { sun_x, sun_height, -far_plane, 0.5f };

	GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat high_shininess[] = { 100.0f };

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

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
	glutMouseFunc(MouseFunc); // handles mouse strokes
	glutMotionFunc(MotionFunc); // handles mouse motions when one or more mouse button is pressed - use this for changing camera view
	//glutFullScreen();

	car = new Car(Color(0.39f, 0.0f, 0.19f, 1.0f), Vector(0.5f, 1.0f, -10.0f), 1.0f, 1.0f, 2.0f);

	InitEnvironment();
	glutMainLoop();

	return EXIT_SUCCESS;
}

// TODO multiple key presses
// TODO change camera view with mouse movement
// TODO gluLookAt when pressed q || e does not implement desired functionality

// TODO use bezier curves for drawing track/road
// TODO draw sky_box using Cylinder class, not the function