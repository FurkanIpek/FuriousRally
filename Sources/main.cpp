#include "Utils\includes.h"

Car car;

static void Reshape(int width, int height)
{
	if (height <= 0)
		height = 1;

	const int aspectratio = width / height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(60.0f, aspectratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	// camera is focused on the car from 10.0f coordinates behind
	Camera::getInstance().setEyePos(Vector(car.center.getX(), car.center.getY(), car.center.getZ() + 10.0f));
	Camera::getInstance().setCenter(car.center);
	Camera::getInstance().setTilt(Vector(0.0f, 1.0f, 0.0f));
	// move function also sets gluLookAt to necessary position
	Camera::getInstance().move(0.0f, 0.0f, 0.0f);
}

static void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.64, 0.80, 0.50, 1);

	car.draw();
	
	glutSwapBuffers();
}

static void Idle(void)
{
	glutPostRedisplay();
}

static void KeyPress(unsigned char keyPressed, int x, int y)
{
	Vector vec(0, 0, 0);

	if (keyPressed == 'w') {
		vec.setZ(-0.1f);
	}
	if (keyPressed == 's') {
		vec.setZ(0.1f);
	}
	if (keyPressed == 'a') {
		vec.setX(-0.1f);
	}
	if (keyPressed == 'd') {
		vec.setX(0.1f);
	}
	if (keyPressed == 'q') {
		Camera::getInstance().lookThroughMe(
			Vector(
				Camera::getInstance().getEyePos().getX() + Camera::getInstance().getEyePos().getZ(),
				Camera::getInstance().getEyePos().getY(),
				Camera::getInstance().getEyePos().getZ()
				)
			);
	}
	if (keyPressed == 'e') {
		Camera::getInstance().lookThroughMe(
			Vector(
				Camera::getInstance().getEyePos().getX() - Camera::getInstance().getEyePos().getZ(),
				Camera::getInstance().getEyePos().getY(),
				Camera::getInstance().getEyePos().getZ()
				)
			);
	}
	
	car.move(vec.getX(), vec.getY(), vec.getZ());
	//Camera::getInstance().move(vec.getX(), vec.getY(), vec.getZ());

	if (keyPressed == 'h')
		glutExit();

	if (keyPressed == 'p')
		gluLookAt(2.0f, 0.5f, 0.0f, 2.0f, 0.5f, -10.0f, 10.0f, 5.0f, 50.0f);
	
	glutPostRedisplay();
}

void InitEnvironment()
{
	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

	GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat high_shininess[] = { 100.0f };

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

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
	
	if (glewInit() != GLEW_OK)
		return EXIT_FAILURE;

	glutIdleFunc(Idle);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(KeyPress);
	glutMouseFunc(NULL);
	//glutFullScreen();

	InitEnvironment();
	glutMainLoop();

	return EXIT_SUCCESS;
}

// TODO create a map using blend & mesh
// TODO multiple key presses
// TODO change camera view with mouse movement

// TODO gluLookAt when pressed q || e does not implement desired functionality

// TODO should I use glut?

// HACK learn how to update screen continuously even if there are no user input