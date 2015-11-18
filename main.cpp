#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>

#include "Sources\Shapes\Triangle.h"
#include "Sources\Shapes\Sphere.h"

Sphere* sphere = new Sphere(Vector(0.5f, 0.05f, 0.0f), 0.5f, Color(0.7f, 0.4f, 0.53f, 0.5f));
Triangle* triangle = new Triangle(Vector(-0.05f, -0.05f, 0.0f), Vector(0.05f, -0.05f, 0.0f),
	Vector(0.0f, 0.05f, 0.0f), Color(0.56f, 0.15f, 0.80f, 1.0f));

static void Reshape(int width = 800, int height = 600)
{
	const float ar = (float)width / (float)height;
	static int a = 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	//glFrustum(-ar, ar, 0.0, 1.0, 0 + a, -1 + a++);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.64, 0.80, 0.50, 1);

	sphere->draw();
	triangle->draw();
	
	// TODO make a rectangular class
	Vector way11(-1.0f, 0, 0), way12(0, 0, -1.0f); // yolun sol çizgisi
	Vector way21(1.0f, 0, 0), way22(0, 0, -1.0f); // yolun sað çizgisi
	//glDrawArrays(GL_POLYGON, 0, 4);
	
	glutSwapBuffers();
}

static void KeyPress(unsigned char keyPressed, int x, int y)
{
	if (keyPressed == 'w') {
		sphere->move(0, 0, -0.1f);
		triangle->move(0, 0, -0.1f);
	}
	if (keyPressed == 's') {
		sphere->move(0, 0, 0.1f);
		triangle->move(0, 0, 0.1f);
	}
	if (keyPressed == 'a') {
		sphere->move(-0.1f, 0, 0);
		triangle->move(-0.1f, 0, 0);
	}
	if (keyPressed == 'd') {
		sphere->move(0.1f, 0, 0);
		triangle->move(0.1f, 0, 0);
	}
	if (keyPressed == 'q')
		glutExit();

	if (keyPressed == 'p')
		gluLookAt(0, 1.5f, -0.5f, 0, 0, 0, 0, 1, 0);

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

	glutDisplayFunc(Display);
	glutKeyboardFunc(KeyPress);
	//glutReshapeFunc(Reshape);
	
	InitEnvironment();
	glutMainLoop();

	return EXIT_SUCCESS;
}