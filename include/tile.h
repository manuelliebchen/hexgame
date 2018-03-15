#ifndef _TILE_
#define _TILE_

#include <GL/glut.h>

#include <map>

#include "color.h"
#include "figure.h"
#include "bush.h"
#include "coin.h"
#include "vec2.h"
#include "constants.h"

class Tile {
  Figure* figure;
  Color color_variation;
  int height;

  Tile( const Tile& tile) = delete;
  const Tile& operator= (const Tile& tile) = delete;

public:
  Tile() {
    color_variation = Color( randf() * 16,randf() * 16, randf() * 16);
    height = 1;
    figure = nullptr;
   };
  ~Tile() { if( figure) delete figure;};
  Figure*& getFigure() { return figure;};
  void clear() {
    delete figure;
    figure = nullptr;
  };
  int getHeight() const { return height;};
  bool isWalkable() const { return (height > 0 && !figure);};

  void draw( const std::map<int,Color>& color_map) const;
  void mark() const;

  void raise( int amount) {
    height += amount;
    if( height <= 0) {
      clear();
    }
  };
  void plant() {
    if( height > 0) {
      figure = new Bush();
    }
  };
};

#endif
