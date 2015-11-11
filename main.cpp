#include "GL\glew.h"
#include "GL\freeglut.h"

void cbFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.64, 0.20, 0.90, 1.0);
	glutSwapBuffers();
}

int main(int argc, char* argv [])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("Furious Rally");

	glutDisplayFunc(cbFunc);

	glutMainLoop();

	return 0;
}