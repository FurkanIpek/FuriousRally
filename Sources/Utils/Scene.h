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
	void move();
	void moveAIcars();
	void draw();
	void setCameraPos();
};