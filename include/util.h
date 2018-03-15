#ifndef _UTIL_
#define _UTIL_

#include "vec2.h"
#include <cmath>
#include <random>
#include <iostream>
#include <GL/glut.h>
#include "constants.h"

class vec2;

float randf();
vec2 getHexCorner( int n);
void glVertex(vec2 vector);

#endif
