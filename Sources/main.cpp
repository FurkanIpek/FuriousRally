#include "Utils\\Scene.h"

static void Reshape(int width, int height)
{
	if (height <= 0)
		height = 1;

	const int aspectratio = width / height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(65.0f, aspectratio, 0.1f, far_plane);

	//setCameraPos();
	Scene::getInstance().setCameraPos();
}

static void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.64, 0.80, 0.50, 1.0f);

	Scene::getInstance().draw();

	glutSwapBuffers();
}

static void KeyRelease(unsigned char keyPressed, int x, int y)
{
	keyPressed = tolower(keyPressed);
	Scene::getInstance().setKey(keyPressed, false);
}

static void KeyPress(unsigned char keyPressed, int x, int y)
{
	keyPressed = tolower(keyPressed);
	Scene::getInstance().setKey(keyPressed, true);
}

static void Idle(void)
{
	Scene::getInstance().keyHandler();
	Display();
}

void InitEnvironment()
{
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { sun_x, sun_height, -far_plane, 1.0f };

	GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat high_shininess[] = { 100.0f };

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

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
	
	InitEnvironment();
	glutMainLoop();

	return EXIT_SUCCESS;
}

// TODO use bezier curves for drawing track/road
// TODO AI car movement
// TODO collision detection
// TODO exhaust smoke
// TODO mouse ile kullanýcý her yerde gezebilmeli