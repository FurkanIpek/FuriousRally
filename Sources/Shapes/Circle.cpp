#include "Circle.h"

Circle::Circle() {}

Circle::Circle(Vector c, double r, Color clr) : center(c), radius(r) { color = clr; }

Circle::~Circle() {}

Color Circle::getColor()
{
	return color;
}

void Circle::draw()
{
	int num_segments = 300;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 

		float x = radius * cosf(theta);//calculate the x component 
		float y = radius * sinf(theta);//calculate the y component 

		glVertex2f(x + center.getX(), y + center.getY());//output vertex 

	}
	glEnd();
}

void Circle::move(GLfloat xv, GLfloat yv, GLfloat zv)
{

}