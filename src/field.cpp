#include "field.h"

Field::Field( unsigned _width, unsigned _height) :
  tile_size( vec2( three_sqrt_half, 0.75f)),
  width( _width),
  height( _height),
  tiles( new Tile[width * height])
{
  for( unsigned i = 0; i < width * height; ++i) {
    Position pos( i%width, i/width);
    tiles[i] = Tile( Color( randf() * 128 + 127,randf() * 128 + 127, randf() * 128 + 127));
  }
  std::cout << "Field Size: " << width << " " << height << std::endl;
}

Field::~Field() {
  delete[] tiles;
}

void Field::draw() {
  glTranslatef( -0.5f * width * tile_size.x, -0.5f * height * tile_size.y, 0);
  for( unsigned i = 0; i < width * height; ++i) {
    glPushMatrix();
    vec2 vector = getVectorPosition( Position( i % width, i/width));
    glTranslatef( vector.x, vector.y, 0);
    tiles[i].draw();
    glPopMatrix();
  }
}

void
Field::drawLine(std::vector<Tile*> way){
    glBegin( GL_LINE_STRIP);
    for( Tile* tile : way) {
      vec2 vector_position = getVectorPosition( getPosition(tile));
      glVertex2f( vector_position.x, vector_position.y);
    }
    glEnd();

    glColor3f( 0, 1, 1);
    for( Tile* tile : way) {
      vec2 vec_pos = getVectorPosition(getPosition(tile));
      std::vector<Tile*> surrounding = getSurounding(tile);
      for( Tile* position : surrounding) {
        vec2 vec_pos_neighbor = getVectorPosition(getPosition(position));
        glBegin( GL_LINE_STRIP);
        glVertex2f( vec_pos.x, vec_pos.y);
        glVertex2f( vec_pos_neighbor.x, vec_pos_neighbor.y);
        glEnd();
      }
    }
}

std::vector<Tile*>
Field::getWay( Position start, Position destination) {
  //The Closed Nodes
  std::vector<Position> visited;

  //Heuristics Costs
  std::map< Position, float> costs;

  //Way allready gone
  std::map< Position, int> way_length;

  //Come From
  std::map< Position, Position> come_from;

  //The Open Nodes
  auto cmp = [&costs](Position pos1, Position pos2) -> bool { return costs[pos1] > costs[pos2];};
  std::priority_queue<Position, std::vector<Position>, decltype(cmp)> queue(cmp);
  std::vector<Position> open;

  queue.push( start);
  open.push_back( start);
  way_length[ start] = 0;
  costs[ start] = sqrt( (start.x - destination.x) * (start.x - destination.x) + (start.y - destination.y) * (start.y - destination.y));

  while( !queue.empty()) {
    Position top = queue.top();
    queue.pop();
    open.erase( std::find( open.begin(), open.end(), top));
    if( queue.size() != open.size()) {
      std::cout << "Oh No! Another Size" << std::endl;
    }
    visited.push_back( top);

    if( destination == top) {
      glBegin( GL_POINTS);
      for( Position pos : visited) {
        std::cout << pos << std::endl;
        glVertex( getVectorPosition( pos));
      }
      glEnd();
      std::vector< Tile*> way;
      Position current = destination;
      while( !(current == start)) {
        Tile* tile = getTile( current);
        way.push_back( tile);
        if( current == come_from[current]) {
          std::cout << "Autsch That went wrong!" << std::endl;
          return way;
        }
        current = come_from[current];
      }
      way.push_back(getTile( start));
      return way;
    }

    for( Position neighbor : getSurounding( top)) {
      if( !getTile( neighbor)) continue;

      if( std::find(visited.begin(), visited.end(), neighbor) != visited.end()) {
        continue;
      }

      if( std::find(open.begin(), open.end(), neighbor) == open.end()) {
        queue.push( neighbor);
        open.push_back( neighbor);
      }

      float cost = way_length[top] + 1;
      if( way_length.find( neighbor) != way_length.end() && cost >= way_length[neighbor]) {
        continue;
      }

      come_from[neighbor] = top;
      way_length[neighbor] = cost;
      float heuristics = sqrt( (neighbor.x - destination.x) * (neighbor.x - destination.x) + (neighbor.y - destination.y) * (neighbor.y - destination.y));
      costs[neighbor] = cost + heuristics;
    }
  }
  return std::vector<Tile*>();
}

std::vector<Position>
Field::getSurounding( Position pos){
    std::vector< Position> surounding;
    surounding.push_back( Position( pos.x -1, pos.y));
    surounding.push_back( Position( pos.x +1, pos.y));
    if( pos.y %2 == 0) {
      surounding.push_back( Position( pos.x , pos.y-1));
      surounding.push_back( Position( pos.x -1, pos.y-1));
      surounding.push_back( Position( pos.x , pos.y+1));
      surounding.push_back( Position( pos.x -1, pos.y+1));
    } else {
      surounding.push_back( Position( pos.x , pos.y-1));
      surounding.push_back( Position( pos.x +1, pos.y-1));
      surounding.push_back( Position( pos.x , pos.y+1));
      surounding.push_back( Position( pos.x +1, pos.y+1));
    }
    return surounding;
}

std::vector<Tile*>
Field::getSurounding( Tile* tile) {
  Position pos = getPosition(tile);
  std::vector<Position> surronding = getSurounding( pos);
  std::vector<Tile*> neighbors;
  for( Position neighbor : surronding){
    if( Tile * tile = getTile( neighbor)){
      neighbors.push_back(tile);
    }
  }
  return neighbors;
}

void
Field::glPosition( Position pos) {
  vec2 vector = getVectorPosition( pos);
  glVertex( vector);
}

Tile*
Field::getTile( const Position& position) {
  if( position.x < 0 || position.x >= (int) width || position.y < 0 || position.y >= (int) height) {
    return nullptr;
  }
  return tiles + position.x + width * position.y;
}

Position
Field::getPosition( const Tile* tile) {
  if( tile < tiles || tile > tiles + width* height) {
    return Position(-1,-1);
  }
  unsigned tile_position = tile - tiles;
  return Position( tile_position % width, tile_position / width);
}

vec2
Field::getVectorPosition( Position pos) {
  return vec2((pos.x + ( pos.y % 2 == 1 ? 0.25f : -0.25 ) + 0.5f) * tile_size.x, (pos.y + 0.5f) * tile_size.y);
}
