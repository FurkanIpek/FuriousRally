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

	Scene::getInstance().setCameraPos();
}

static void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.59f, 0.79f, 0.98f, 1.0f);

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

int main(int argc, char* argv [])
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_ALPHA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
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
	
	glutMainLoop();

	return EXIT_SUCCESS;
}
// TODO back face culling
// TODO Curves slaytı, sayfa 140, bezier curves
// TODO antialiasing in RasterDisplay slayt - look into it
// TODO exhaust smoke
// TODO camera should move around with mouse when "move around with mouse" mode is on

// TODO camera arabayla beraber rotate etmeli