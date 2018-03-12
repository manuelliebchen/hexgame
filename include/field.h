#ifndef _FIELD_
#define _FIELD_

#include <GL/glut.h>
#include <queue>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

#include "position.h"
#include "tile.h"
#include "util.h"

class Field {

public:
  Field( unsigned _width, unsigned _heigth);
  ~Field();

  void draw();
  void drawLine(std::vector<Tile*> way);

  unsigned getDistance( Position start, Position destination);
  std::vector<Tile*> getWay( Position start, Position destination);
  std::vector<Position> getSurounding( Position position);
  std::vector<Tile*> getSurounding( Tile* position);

  Tile* getTile( const Position& position);
  Position getPosition( const Tile* tile);
  vec2 getVectorPosition( Position pos);
  void glPosition( Position pos);

private:
  vec2 tile_size;
  unsigned width;
  unsigned height;
  Tile* tiles;

  Field( const Field& field);
  const Field& operator= ( const Field& field);

  struct smallerDist {
    bool operator() (std::pair<Position,float> pos1, std::pair<Position,float> pos2) {
      return pos1.second < pos1.second;
    }
  };
};

#endif
