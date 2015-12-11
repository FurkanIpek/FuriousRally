#pragma once
#include "includes.h"

class Scene {
private:
	Car* car;
	Camera scene_cam;
	Car* car_2;
	Sphere* sun;
	Cube* skyCube;

	std::vector<Car*> AIcars;
	std::vector<Shape*> objects;

	bool keys[256] = { false };

	Scene();
	void ground();

	Scene(Scene const&);              // Don't Implement
	void operator=(Scene const&);	  // Don't implement

public:
	static Scene& getInstance()
	{
		static Scene scene;

		return scene;
	}

	void setKey(unsigned char key, bool condition) { keys[(int)key] = condition; }
	bool getKey(int pos) { return keys[pos]; }
	void keyHandler();

	void draw() 
	{ 
		car->draw();
		
		for (auto car : AIcars)
			car->draw();

		for (auto obj : objects)
			obj->draw();

		ground();
	}

	void setCameraPos()
	{
		scene_cam.setEyePos(Vector(car->getCenter().getX(), car->getCenter().getY() + 2.0f, car->getCenter().getZ() + 7.0f));
		scene_cam.setCenter(car->getCenter());
		scene_cam.setTilt(Vector(0.0f, 1.0f, 0.0f));

		scene_cam.move(0.0f, 0.0f, 0.0f);
	}
};