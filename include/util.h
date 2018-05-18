#ifndef _UTIL_
#define _UTIL_

#include <GL/glut.h>
#include <cmath>
#include <random>
#include <iostream>

#include "vec2.h"
#include "constants.h"

class vec2;

float randf();
vec2  getHexCorner(int n);
float areaOfHexagon(float radius);

#endif
