#include "tile.h"

void Tile::draw( const std::map<int,Color>& color_map) const {
  glPushMatrix();
  Color color = (color_map.lower_bound( height)->second);
  color = Color( color.red + color_variation.red,  color.green + color_variation.green,  color.blue + color_variation.blue);
  if( height > 0) {
    glColor3f(color.red/256.0f * 0.5f, color.green/256.0f * 0.5f, color.blue/256.0f * 0.5f);
    glBegin(GL_POLYGON);
    for( unsigned i = 0; i < 3 ; ++i) {
      vec2 corner = getHexCorner(i);
      glVertex2f( corner.x * 0.5f, corner.y * 0.5f + height * TILE_STEP_HEIGHT);
    }
    for( unsigned i = 3; i < 6 ; ++i) {
      vec2 corner = getHexCorner(i);
      glVertex2f( corner.x * 0.5f, corner.y * 0.5f);
    }
    glEnd();
    glTranslatef( 0, height * TILE_STEP_HEIGHT, 0);
  }
  glColor3f(color.red/256.0f * 0.8f, color.green/256.0f * 0.8f, color.blue/256.0f * 0.8f);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i);
    glVertex2f( corner.x * 0.5f, corner.y * 0.5f);
  }
  glEnd();
  glColor3f(color.red/256.0f, color.green/256.0f, color.blue/256.0f);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i);
    glVertex2f( corner.x * 0.4f, corner.y * 0.4f);
  }
  glEnd();
  if(figure) {
    figure->draw();
  }
  glPopMatrix();
}

void
Tile::mark() const {
  glPushMatrix();
  // glTranslatef( 0, height * TILE_STEP_HEIGHT, 0);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i);
    glVertex2f( corner.x * 0.5f, corner.y * 0.5f);
  }
  glEnd();
  glPopMatrix();
}
