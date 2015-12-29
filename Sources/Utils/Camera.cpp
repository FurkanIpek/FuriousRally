#include "Camera.h"

#include <math.h>

void Camera::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat add = cos(angle) * camDistance;
	eye.setX(eye.getX() + add);
	lookThroughMe();
}