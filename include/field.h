#ifndef _FIELD_
#define _FIELD_

#include <GL/glut.h>

#include <queue>
#include <vector>
#include <array>
#include <map>

#include <utility>
#include <algorithm>

#include <cstdlib>
#include <cmath>
#include <cassert>

#include "constants.h"
#include "position.h"
#include "tile.h"
#include "bush.h"
#include "util.h"

class Field {
private:
  unsigned size[2];
  Tile* tiles;

  std::map<int, Color> color_map;

  Field( const Field& field);
  const Field& operator= ( const Field& field);

public:
  Field(unsigned width, unsigned height);
  Field(unsigned width, unsigned height, unsigned discrepancy, unsigned smoothing);
  ~Field();

  void raise( Tile* tile, int amount);
  void smoothen( unsigned amount);
  void smoothen( std::vector<Tile*> to_smooth);
  void forestify( unsigned amount);

  void draw( vec2 translation) const;
  void mark( vec2 translation, std::vector<Tile*> path) const;

  Tile* estimatTile( vec2 pos) const;
  std::vector<Tile*> findPath( Tile* start_tile, Tile* destination_tile) const;

  Tile* getTile( const Position& position) const;
  Position getPosition( const Tile* tile) const;
  vec2 getVectorPosition( Tile* pos) const;
  vec2 getDrawingPosition( Tile* pos) const;

  std::vector<Tile*> findSurounding( Tile* start_tile, int n) const;
  std::vector<Tile*> getSurounding( Tile* position) const;
  float heuristic( Tile* start, Tile* end) const;

  const unsigned* getSize() const { return size;};
};

#endif
