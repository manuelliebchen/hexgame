#include "tile.h"

void Tile::draw( vec2 position, const std::map<int,Color>& color_map) const {
  Color color = (color_map.lower_bound( height)->second);
  color = Color( color.red + color_variation.red,  color.green + color_variation.green,  color.blue + color_variation.blue);
  if( height > 0) {
    glColor3f(color.red/256.0f * 0.5f, color.green/256.0f * 0.5f, color.blue/256.0f * 0.5f);
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
  }
  position += vec2( 0, height * TILE_STEP_HEIGHT);
  glColor3f(color.red/256.0f * 0.8f, color.green/256.0f * 0.8f, color.blue/256.0f * 0.8f);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i) * 0.5f + position;
    glVertex2f( corner.x, corner.y);
  }
  glEnd();
  glColor3f(color.red/256.0f, color.green/256.0f, color.blue/256.0f);
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
