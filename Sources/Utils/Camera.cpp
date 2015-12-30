#include "Camera.h"
#include "Constants.h"

#include <math.h>
#include <stdio.h>

Camera::Camera()
{
	eye = Vector(0.0f, 0.0f, 0.0f);
	center = Vector(0.0f, 0.0f, -1.0f);
	tilt = Vector(0.0f, 1.0f, 0.0f);
	angle = 0.0f;

	lookThroughMe();
}

void Camera::rotate(GLfloat angle)
{
	this->angle += angle;
}

void Camera::changeView(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	Vector v = eye;
	eye.setX(0.f);
	eye.setY(2.0f);
	eye.setZ(camDistance);
	eye.rotate(angle, x, y, z);
	eye.translate(v);
}

void Camera::setEyePos(Vector v)
{
	eye.setX(0.f);
	eye.setY(2.0f);
	eye.setZ(camDistance);
	eye.rotate(angle, 0.f, 1.f, 0.f);
	eye.translate(v);
}

void Camera::lookThroughMe()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye.getX(), eye.getY(), eye.getZ(),
		center.getX(), center.getY(), center.getZ(),
		tilt.getX(), tilt.getY(), tilt.getZ());
}

void Camera::lookThroughMe(Vector eye_pos)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye_pos.getX(), eye_pos.getY(), eye_pos.getZ(),
		center.getX(), center.getY(), center.getZ(),
		tilt.getX(), tilt.getY(), tilt.getZ());
}