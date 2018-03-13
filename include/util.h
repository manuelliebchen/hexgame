#ifndef _UTIL_
#define _UTIL_

#define EPSILON (0.00001f)
#define PI (3.14159f)
#define PHI (2.39996f)
#define INV_PI (0.318309f)
#define three_sqrt_half (0.866025f)
#define tile_size (vec2( three_sqrt_half, 0.75f))

#include "vec2.h"
#include <cmath>
#include <random>
#include <iostream>
#include <GL/glut.h>

class vec2;

float randf();
vec2 getHexCorner( int n);
void glVertex(vec2 vector);

#endif
