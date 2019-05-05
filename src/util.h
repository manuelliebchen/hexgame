#ifndef _UTIL_
#define _UTIL_

#include <GL/glut.h>
#include <cmath>
#include <random>
#include <iostream>

#include "glm/glm.hpp"

#include "constants.h"

typedef glm::vec2 vec2;

vec2  getHexCorner(int n);
float areaOfHexagon(float radius);

#endif
