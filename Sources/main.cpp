#include "Utils\\Scene.h"

bool started = false;

static void Reshape(int width, int height)
{
	if (height <= 0)
		height = 1;

	const int aspectratio = width / height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef(1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(65.0f, aspectratio, 0.1f, far_plane);

	Scene::getInstance().setCameraPos();
}

static void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(Color::getColor(BLUE).getRed(), Color::getColor(BLUE).getGreen(), Color::getColor(BLUE).getBlue(), 1.0f);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Scene::getInstance().draw();

	if (!started)
	{
		char* string = "Game is about to begin, hold on tight!";
		glRasterPos3f(-1.0f, 3.0f, -10.0f);
		//get the length of the string to display
		int len = (int)strlen(string);

		//loop to display character by character
		for (int i = 0; i < len; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
		}
	}

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

static void mouseFunc(int button, int state, int x, int y)
{
	static GLfloat old = 0.f;
	
	//printf("Here with %i %i\n", button, state);

	if (button == 3 && state == 0)
		Scene::getInstance().zoom += 5.f;
	else if (button == 4 && state == 0)
		Scene::getInstance().zoom -= 5.f;
	else if (button == 0 && state == 0)
		Scene::getInstance().trX += 1.f;
	else if (button == 2 && state == 0)
		Scene::getInstance().trX -= 1.f;
}

static void motionFunc(int x, int y)
{
	static GLfloat oldX = 0.f, oldY = 0.f;
	GLfloat diffX = oldX - x, diffY = oldY - y;
	GLfloat facX = 0.1f, facY = 0.1f;
	// printf("%f %f\n", diffX, diffY);// x column - y row

	//if (diffX < 20.f)
		Scene::getInstance().trY += diffY / 2.f;
	//if (diffY < 20.f)
		//Scene::getInstance().trY += diffY / 10.f;

	oldX = x; oldY = y;
}

void initGlut(int val)
{
	started = true;
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyPress);
	glutKeyboardUpFunc(KeyRelease);
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
	
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMotionFunc(motionFunc);
	glutMouseFunc(mouseFunc);
	
	glutTimerFunc(5000, initGlut, 0);
	glutMainLoop();

	return EXIT_SUCCESS;
}
// TODO back face culling
// TODO Curves slaytı, sayfa 140, bezier curves
// TODO antialiasing in RasterDisplay slayt - look into it
// TODO camera should move around with mouse when "move around with mouse" mode is on