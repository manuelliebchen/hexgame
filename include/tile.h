#ifndef _TILE_
#define _TILE_

#define TILE_STEP_HEIGHT 0.1f

#include <GL/glut.h>

#include "color.h"
#include "figure.h"
#include "vec2.h"

class Tile {
  Color color;
  Figure* figure;
  int height;

public:
  Tile() {};
  ~Tile() { if( figure) delete figure;};
  Tile( Color _color, int _height);
  Figure*& getFigure() { return figure;};
  void raise( int amount) { height += amount;};
  int getHeight() { return height;};

  void draw();
  void mark();
};

#endif
