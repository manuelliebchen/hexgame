#include "tile.h"

void Tile::draw( vec2 position, const std::map<int,Color>& color_map) const {
  Color color = (color_map.lower_bound( height)->second);
  color = Color( color.red + color_variation.red,  color.green + color_variation.green,  color.blue + color_variation.blue);
  if( height > 0) {
    glColor3ub(color.red/2, color.green/2, color.blue/2);
    glBegin(GL_POLYGON);
    for( unsigned i = 0; i < 3 ; ++i) {
      vec2 corner = getHexCorner(i) * 0.5f + position;
      glVertex2f( corner.x, corner.y + height * TILE_STEP_HEIGHT);
    }
    for( unsigned i = 3; i < 6 ; ++i) {
      vec2 corner = getHexCorner(i) * 0.5f + position;
      glVertex2f( corner.x, corner.y);
    }
    glEnd();
    position += vec2( 0, height * TILE_STEP_HEIGHT);
  }
  glColor3ub(color.red/5 * 4, color.green/5 * 4, color.blue/5 * 4);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i) * 0.5f + position;
    glVertex2f( corner.x, corner.y);
  }
  glEnd();
  glColor3ub(color.red, color.green, color.blue);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i) * 0.4f + position;
    glVertex2f( corner.x, corner.y);
  }
  glEnd();
  if(figure) {
    figure->draw( position);
  }
}

void
Tile::mark(vec2 translation) const {
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i) * 0.5f + translation;
    glVertex2f( corner.x, corner.y);
  }
  glEnd();
}
