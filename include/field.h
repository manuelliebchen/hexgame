#ifndef _FIELD_
#define _FIELD_

#define PATH_HEIGHT_DISCREPANCY 3

#include <GL/glut.h>
#include <queue>
#include <vector>
#include <array>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cassert>

#include "position.h"
#include "tile.h"
#include "util.h"

class Field {
private:
  unsigned size[2];
  Tile* tiles;

  Field( const Field& field);
  const Field& operator= ( const Field& field);

public:
  Field(unsigned width, unsigned height, unsigned discrepancy, unsigned smoothing);
  ~Field();

  void draw();
  void drawPath(std::vector<Tile*> path);

  unsigned getDistance( Position start, Position destination);
  std::vector<Tile*> findPath( Tile* start_tile, Tile* destination_tile);
  std::vector<Tile*> findSurounding( Tile* start_tile, int n);
  std::vector<Position> getSurounding( Position position);
  std::vector<Tile*> getSurounding( Tile* position);

  bool raise( Tile* tile, int amount);

  Tile* getTile( vec2 pos);
  Tile* getTile( const Position& position);
  Position getPosition( const Tile* tile);
  vec2 getVectorPosition( Position pos);
  vec2 getVectorPosition( Tile* pos);
  void glPosition( Position pos);
  void glDrawPoints( std::vector<Position>& points);

  const unsigned* getSize() { return size;};
};

#endif
