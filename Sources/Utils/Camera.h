#pragma once

#include "Vector.h"
#include "Constants.h"

class Camera {
private:
	Vector eye, center, tilt;
	GLfloat angle;

	Camera();

public:
	static Camera& instance()
	{
		static Camera camera;
		return camera;
	}

	void setEyePos(Vector v);
	void setCenter(Vector v) { center = v; }
	void setTilt(Vector v) { tilt = v; }

	Vector getEyePos() { return eye; }
	Vector getCenter() { return center; }
	Vector getTilt() { return tilt; }

	void lookThroughMe();
	void lookThroughMe(Vector eye_pos);
	void rotate(GLfloat angle);
	void changeView(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void resetAngle() { angle = 0.0f; }
};