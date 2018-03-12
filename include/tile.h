#ifndef _TILE_
#define _TILE_

#include <GL/glut.h>

#include "color.h"
#include "figure.h"
#include "vec2.h"

class Tile {
  Color color;
  Figure* figure;

public:
  Tile() {};
  Tile( Color _color);

  Tile( const Tile& tile);
  const Tile& operator= (const Tile& tile);

  void draw();

};

#endif
