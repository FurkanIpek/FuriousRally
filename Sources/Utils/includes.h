#pragma once
// glew and glut are also included in any Shape class, by including "Shape.h"
// I also added these inclusions here so that reader knows what libraries are used
#include "GL\glew.h"
#include "GL\freeglut.h"

#ifdef _DEBUG
#include <iostream>
#endif

#include "..\Shapes\Circle.h"
#include "..\Shapes\Cube.h"
#include "..\Shapes\Sphere.h"
#include "..\Shapes\Triangle.h"

#include "..\Objects\Car.h"

#include "Camera.h"
#include "Color.h"
#include "Vector.h"
