#include "field.h"

Field::Field(unsigned _width, unsigned _height) :
  size{ _width, _height},
  tiles( new Tile[size[0]* size[1]])
{
  color_map = initializeColorMap();
}

Field::Field(unsigned _width, unsigned _height, unsigned discrepancy, unsigned smoothing) :
  size{ _width, _height},
  tiles( new Tile[size[0]* size[1]])
{
  color_map = initializeColorMap();
  for( unsigned i = 0; i < size[0] * size[1]; ++i) {
    int height = round(discrepancy * (randf() - 0.5f))+1;
    tiles[i].raise( height);
  }
  smoothen( smoothing);
  forestify( 4);
  Tile* tile = tiles + rand() % size[0] + rand() % size[1] * size[0];
  while( !tile->isWalkable() ) {
    tile = tiles + rand() % size[0] + rand() % size[1] * size[0];
  }
  tile->place( new Player( tile));
}

Field::~Field() {
  delete[] tiles;
}

std::map<int,Color>
Field::initializeColorMap() {
  std::map<int,Color> color_map;
  color_map[-128] = Color( 10,  30, 60);
  color_map[-5]    = Color( 10,  30, 60);
  color_map[0]    = Color( 20,  59,122);
  color_map[1]    = Color(240, 203, 25);
  color_map[7]    = Color( 48, 128, 32);
  color_map[10]   = Color( 112,112,112);
  color_map[256]  = Color( 240,240,240);
  return color_map;
}

void Field::draw( vec2 translation) const {
  for( int i = (size[0] * size[1]) -1; i >= 0; --i) {
    vec2 vector = getVectorPosition( tiles + i) + translation;
    tiles[i].draw( vector, color_map);
  }
}

void
Field::mark( vec2 translation, std::vector<Tile*> path) const {
    for( Tile* tile : path) {
      vec2 vector = getDrawingPosition( tile) + translation;
      tile->mark(vector);
    }
}

void
Field::smoothen( unsigned amount) {
  for( unsigned j = 0; j < amount; j++){
    std::vector<int> raising( size[0] * size[1], 0);
    for( unsigned i = 0; i < size[0] * size[1]; ++i) {
      int sum = 0;
      std::vector<Tile*> neighbors = getSurounding( tiles + i);
      for( Tile* neighbor : neighbors){
        int height = neighbor->getHeight();
        sum += height;
      }
      sum = round( sum / (float)neighbors.size());
      sum -= tiles[i].getHeight();
      raising[i] = sum;
    }
    for( unsigned i = 0; i < size[0] * size[1]; ++i) {
      tiles[i].raise(raising[i]);
    }
  }
}

void
Field::smoothen( std::vector<Tile*> to_smooth) {
  std::map<Tile*, int> raising;
  for( Tile* tile : to_smooth) {
    int sum = 0;
    std::vector<Tile*> neighbors = getSurounding( tile);
    for( Tile* neighbor : neighbors){
      int height = neighbor->getHeight();
      sum += height;
    }
    sum = round( sum / (float)neighbors.size());
    sum -= tile->getHeight();
    raising[tile] = sum;
  }
  for( Tile* tile : to_smooth) {
    tile->raise(raising[tile]);
  }
}

void
Field::forestify( unsigned amount){
  for( unsigned i = 0; i < size[0] * size[1]; ++i) {
    int height = tiles[i].getHeight();
    if( height > 1 && height <= 7) {
      tiles[i].clear();
      if( randf() > 0.7f) {
        tiles[i].plant();
      }
    }
  }
  for( unsigned j = 0; j < amount; j++){
    std::vector<bool> bush( size[0] * size[1], 0);
    for( unsigned i = 0; i < size[0] * size[1]; ++i) {
      int bushes = 0;
      int land_tile = 0;
      int tile_height = tiles[i].getHeight();
      if( tile_height <= 1 || tile_height > 7) {
        continue;
      }
      std::vector<Tile*> neighbors = getSurounding( tiles + i);
      for( Tile* neighbor : neighbors){
        int height = neighbor->getHeight();
        if( height > 1 && height <= 7) {
          ++land_tile;
        }

        Figure*& tile_figure = neighbor->getFigure();
        if( tile_figure) {
          if( dynamic_cast<Bush*>(tile_figure)) {
            ++bushes;
          }
        }
      }
      bush[i] = bushes >= land_tile / (float)2;
    }
    for( unsigned i = 0; i < size[0] * size[1]; ++i) {
      tiles[i].clear();
      if( bush[i]) {
        tiles[i].plant();
      }
    }
  }
}

float
Field::heuristic( Tile* start, Tile* end) const {
  return three_sqrt_half_inv * (float) ( getVectorPosition(start) - getVectorPosition(end));
}

std::vector<Tile*>
Field::getSurounding( Tile* tile) const {
  if( tile < tiles || tile > tiles + size[0]* size[1]) {
    return std::vector<Tile*>();
  }
  unsigned tile_position = tile - tiles;
  int x = tile_position % size[0];
  int y = tile_position / size[0];
  std::vector<Tile*> surounding;
  int offset = y %2 == 0 ? -1 : 0;
  surounding.push_back( tile_at( x - 1, y));
  surounding.push_back( tile_at( x + offset, y-1));
  surounding.push_back( tile_at( x + 1 + offset, y-1));
  surounding.push_back( tile_at( x + 1, y));
  surounding.push_back( tile_at( x + 1 + offset, y+1));
  surounding.push_back( tile_at( x + offset, y+1));
  for( auto it = surounding.begin(); it != surounding.end(); ++it){
    if( !(*it)) {
      surounding.erase(it);
      --it;
    }
  }
  surounding.shrink_to_fit();
  return surounding;
}

Tile*
Field::tile_at( int x, int y) const {
  if( x < 0 || x >= (int) size[0] || y < 0 || y >= (int) size[1]) {
    return nullptr;
  }
  return tiles + x + size[0] * y;
}

Tile*
Field::estimatTile( vec2 pos) const {
  for( Tile* it = tiles; it != tiles + size[0]*size[1]; ++it) {
    vec2 tile_position = getDrawingPosition( it);
    if( (float) (pos - tile_position) < three_sqrt_half * 0.5f ) {
      return it;
    }
  }
  return nullptr;
}

vec2
Field::getVectorPosition( Tile* tile) const {
  if( tile < tiles || tile > tiles + size[0]* size[1]) {
    return vec2();
  }
  unsigned tile_position = tile - tiles;
  int x = tile_position % size[0];
  int y = tile_position / size[0];
  return vec2((x + ( y % 2 == 1 ? 0.25f : -0.25 ) + 0.5f) * three_sqrt_half, (y + 0.5f) * 0.75f);
}

vec2
Field::getDrawingPosition( Tile* pos) const {
  return getVectorPosition( pos) + (pos->getHeight() > 0 ? vec2( 0, pos->getHeight() * TILE_STEP_HEIGHT) : vec2());
}

std::vector<Tile*>
Field::findPath( Tile* start_tile, Tile* destination_tile) const {
  if(heuristic(start_tile, destination_tile) > TURN_WALKING_DISTANCE * 5) {
    return std::vector<Tile*>();
  }
  if( !destination_tile->isWalkable()) {
    return std::vector<Tile*>();
  }
  vec2 destination_vec = getVectorPosition( destination_tile);

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
  costs[ start_tile] = heuristic(start_tile, destination_tile);

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
      return way;
    }

    for( Tile* neighbor : getSurounding( top)) {
      int neighbor_height = neighbor->getHeight();
      int height_diference = abs(top_height - neighbor_height);
      if( !neighbor->isWalkable() || height_diference >= PATH_HEIGHT_DISCREPANCY){
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
      costs[neighbor] = way + heuristic(neighbor, destination_tile);

      if( std::find(open.begin(), open.end(), neighbor) == open.end()) {
        queue.push( neighbor);
        open.push_back( neighbor);
      }
    }
  }
  return std::vector<Tile*>();
}

std::vector<Tile*>
Field::findSurounding( Tile* start_tile, int n) const {
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
      int neighbor_height = neighbor->getHeight();
      int height_diference = abs(top_height - neighbor_height);
      if( !neighbor->isWalkable() || height_diference >= PATH_HEIGHT_DISCREPANCY){
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
  visited.erase( std::find( visited.begin(), visited.end(), start_tile));
  return visited;
}
