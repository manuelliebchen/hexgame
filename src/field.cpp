#include "field.h"

Field::Field(unsigned _width, unsigned _height, unsigned discrepancy, unsigned smoothing) :
  size{ _width, _height},
  tiles( new Tile[size[0]* size[1]])
{
  for( unsigned i = 0; i < size[0] * size[1]; ++i) {
    Position pos( i%size[0], i/size[0]);
    tiles[i] = Tile( Color( randf() * 128 + 127,randf() * 128 + 127, randf() * 128 + 127), round((randf() - 0.45f) * discrepancy + 1));
  }
  for( unsigned j = 0; j < smoothing; j++){
    std::vector<int> raising( size[0] * size[1], 0);
    for( unsigned i = 0; i < size[0] * size[1]; ++i) {
      int sum = 0;
      std::vector<Tile*> neighbors = getSurounding( tiles + i);
      for( Tile* neighbor : neighbors){
        sum += neighbor->getHeight();
      }
      sum /= (int) neighbors.size();
      sum -= tiles[i].getHeight();
      raising[i] = sum;
    }
    for( unsigned i = 0; i < size[0] * size[1]; ++i) {
      tiles[i].raise(raising[i]);
    }
  }
}

Field::~Field() {
  delete[] tiles;
}

void Field::draw() {
  for( int i = (size[0] * size[1]) -1; i >= 0; --i) {
    glPushMatrix();
      vec2 vector = getVectorPosition( Position( i % size[0], i/size[0]));
      glTranslatef( vector.x, vector.y, 0);
      tiles[i].draw();
    glPopMatrix();
  }
}

void
Field::drawPath(std::vector<Tile*> path){
    for( Tile* tile : path) {
      glPushMatrix();
        vec2 vector = getVectorPosition( tile);
        glTranslatef( vector.x, vector.y, 0);
        tile->mark();
      glPopMatrix();
    }
}

bool
Field::raise( Tile* tile, int amount) {
  tile->raise( amount);
  int tile_height = tile->getHeight();
  int rised = 0;
  std::vector<Tile*> neighbors = getSurounding(tile);
  for( Tile* neighbor : neighbors){
    int height_diference = tile_height - neighbor->getHeight();
    if( height_diference > PATH_HEIGHT_DISCREPANCY) {
      rised += 1;
      raise( neighbor, 1);
    } else if( height_diference < -PATH_HEIGHT_DISCREPANCY) {
      rised -= 1;
      raise( neighbor, -1);
    }
  }
  return rised != 0;
}

std::vector<Tile*>
Field::findPath( Tile* start_tile, Tile* destination_tile) {
  if( (float) ( getVectorPosition( start_tile) - getVectorPosition( destination_tile)) > 15) {
    return std::vector<Tile*>();
  }
  Position start = getPosition(start_tile);
  Position destination = getPosition(destination_tile);
  vec2 destination_vec = getVectorPosition( destination);

  //The Closed Nodes
  std::vector<Tile*> visited;

  //Heuristics Costs
  std::map< Tile*, float> costs;

  //Way allready gone
  std::map< Tile*, int> way_length;

  //Come From
  std::map< Tile*, Tile*> come_from;

  //The Open Nodes
  auto cmp = [&costs](Tile* pos1, Tile* pos2) -> bool { return costs[pos1] > costs[pos2];};
  std::priority_queue<Tile*, std::vector<Tile*>, decltype(cmp)> queue(cmp);
  std::vector<Tile*> open;

  queue.push( start_tile);
  open.push_back( start_tile);
  way_length[ start_tile] = 0;
  costs[ start_tile] = (float) (getVectorPosition( start) - destination_vec);

  while( !queue.empty()) {
    Tile* top = queue.top();
    queue.pop();
    open.erase( std::find( open.begin(), open.end(), top));
    visited.push_back( top);
    int top_height = top->getHeight();

    if( destination_tile == top) {
      std::vector< Tile*> way;
      Tile* current = destination_tile;
      while( !(current == start_tile)) {
        way.push_back( current);
        current = come_from[current];
      }
      way.push_back( start_tile);
      return way;
    }

    for( Tile* neighbor : getSurounding( top)) {
      float neighbor_height = neighbor->getHeight();
      float height_diference = abs(top_height - neighbor_height);
      if( neighbor->getFigure() || height_diference >= PATH_HEIGHT_DISCREPANCY || neighbor_height <= 0){
        continue;
      }
      if( std::find(visited.begin(), visited.end(), neighbor) != visited.end()) {
        continue;
      }

      float way = way_length[top] + 1 + height_diference;
      if( way_length.find( neighbor) != way_length.end() && way >= way_length[neighbor]) {
        continue;
      }

      come_from[neighbor] = top;
      way_length[neighbor] = way;
      float heuristics = (float) (getVectorPosition( neighbor) - destination_vec);
      costs[neighbor] = way + heuristics;

      if( std::find(open.begin(), open.end(), neighbor) == open.end()) {
        queue.push( neighbor);
        open.push_back( neighbor);
      }
    }
  }
  return std::vector<Tile*>();
}

std::vector<Tile*>
Field::findSurounding( Tile* start_tile, int n) {
  //The Closed Nodes
  std::vector<Tile*> visited;

  //Way allready gone
  std::map< Tile*, int> way_length;

  //The Open Nodes
  auto cmp = [&way_length](Tile* pos1, Tile* pos2) -> bool { return way_length[pos1] > way_length[pos2];};
  std::priority_queue<Tile*, std::vector<Tile*>, decltype(cmp)> queue(cmp);
  std::vector<Tile*> open;

  queue.push( start_tile);
  open.push_back( start_tile);
  way_length[ start_tile] = 0;

  while( !queue.empty()) {
    Tile* top = queue.top();
    queue.pop();
    open.erase( std::find( open.begin(), open.end(), top));
    visited.push_back( top);
    int top_height = top->getHeight();

    for( Tile* neighbor : getSurounding( top)) {
      float neighbor_height = neighbor->getHeight();
      float height_diference = abs(top_height - neighbor_height);
      if( neighbor->getFigure() || height_diference >= PATH_HEIGHT_DISCREPANCY || neighbor_height <= 0){
        continue;
      }
      if( std::find(visited.begin(), visited.end(), neighbor) != visited.end()) {
        continue;
      }

      float way = way_length[top] + 1 + height_diference;
      if( way > n) {
        continue;
      }

      if( way_length.find( neighbor) != way_length.end() && way >= way_length[neighbor]) {
        continue;
      }

      way_length[neighbor] = way;

      if( std::find(open.begin(), open.end(), neighbor) == open.end()) {
        queue.push( neighbor);
        open.push_back( neighbor);
      }
    }
  }
  return visited;
}

void
Field::glDrawPoints( std::vector<Position>& points) {
  glBegin( GL_POINTS);
  for( Position pos : points) {
    glVertex( getVectorPosition( pos));
  }
  glEnd();
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
  if( position.x < 0 || position.x >= (int) size[0] || position.y < 0 || position.y >= (int) size[1]) {
    return nullptr;
  }
  return tiles + position.x + size[0] * position.y;
}

Tile*
Field::getTile( vec2 pos) {
  //TODO find tile
  for( Tile* it = tiles; it != tiles + size[0]*size[1]; ++it) {
    vec2 tile_position = getVectorPosition( it);
    if( (float) (pos - tile_position) < three_sqrt_half * 0.5f ) {
      return it;
    }
  }
  return nullptr;
}

Position
Field::getPosition( const Tile* tile) {
  if( tile < tiles || tile > tiles + size[0]* size[1]) {
    return Position(-1,-1);
  }
  unsigned tile_position = tile - tiles;
  return Position( tile_position % size[0], tile_position / size[0]);
}

vec2
Field::getVectorPosition( Position pos) {
  return vec2((pos.x + ( pos.y % 2 == 1 ? 0.25f : -0.25 ) + 0.5f) * tile_size.x, (pos.y + 0.5f) * tile_size.y);
}

vec2
Field::getVectorPosition( Tile* pos) {
  return getVectorPosition( getPosition( pos)) + (pos->getHeight() > 0 ? vec2( 0, pos->getHeight() * TILE_STEP_HEIGHT) : vec2());
}
