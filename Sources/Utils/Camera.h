#pragma once

#include "Vector.h"

class Camera {
private:
	Vector eye, center, tilt;

	Camera() 
	{
		eye = Vector(0.0f, 0.0f, 0.0f);
		center = Vector(0.0f, 0.0f, -1.0f);
		tilt = Vector(0.0f, 1.0f, 0.0f);

		lookThroughMe();
	}

	void lookThroughMe()
	{
		gluLookAt(eye.getX(), eye.getY(), eye.getZ(),
			center.getX(), center.getY(), center.getZ(),
			tilt.getX(), tilt.getY(), tilt.getZ());
	}

	Camera(const Camera&);
	void operator=(const Camera&);

public:
	static Camera& getInstance()
	{
		static Camera camera;

		return camera;
	}

	void setEyePos(Vector v) { eye = v; }
	void setCenter(Vector v) { center = v; }
	void setTilt(Vector v) { tilt = v; }

	Vector getEyePos() { return eye; }
	Vector getCenter() { return center; }
	Vector getTilt() { return tilt; }

	void move(GLfloat xv, GLfloat yv, GLfloat zv)
	{
		Vector translation_vec(xv, yv, zv);

		// tilt should not be changed
		eye.translate(translation_vec);
		center.translate(translation_vec);

		lookThroughMe();
	}

	void lookThroughMe(Vector eye_pos)
	{
		gluLookAt(eye_pos.getX(), eye_pos.getY(), eye_pos.getZ(),
			center.getX(), center.getY(), center.getZ(),
			tilt.getX(), tilt.getY(), tilt.getZ());
	}
};