#pragma once
// glew and glut are also included in any Shape class, by including "Shape.h"
// I also added these inclusions here so that reader knows what libraries are used
#include "GL\glew.h"
#include "GL\freeglut.h"

#include <ctype.h> // for tolower

#ifdef _DEBUG
#include <cstdio>
#endif

#include "..\Shapes\Cube.h"
#include "..\Shapes\Sphere.h"
#include "..\Shapes\Triangle.h"
#include "..\Shapes\Cylinder.h"

#include "..\Objects\Object.h"
#include "..\Objects\Car.h"

#include "Camera.h"
#include "Color.h"
#include "Vector.h"
#include "Constants.h"
#include "Scene.h"
