#pragma once
#include "includes.h"

class Scene {
private:
	Car* car;
	Cube* treasureBox;

	GLfloat x1 = 15.50f, x2 = 100.0f, x3 = -1.0f;

	std::vector<Car*> AIcars;
	std::vector<Shape*> objects;
	std::vector<Fire*> fires;

	bool keys[256] = { false };
	bool cheatMode;

	Scene();
	void ground();
	GLfloat getBezierPoint(GLfloat zet);
	void outOfRoadCheck(Car*);
	void createTreasureBox();
	void prizeCheck();
	void portForward(Car* car);
	void roadHeight(Car* car);
	void isCarReachedFinishLine(Car* car);

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
	void onClose(int val);

	GLfloat trX, trY, zoom, rotation;
};