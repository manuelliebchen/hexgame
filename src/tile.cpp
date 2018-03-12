#include "tile.h"

Tile::Tile( Color _color) :
  color( _color) {}

const Tile& Tile::operator= (const Tile& tile) {
  color = tile.color;
  return *this;
}

void Tile::draw() {
  glPushMatrix();
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
  glPopMatrix();
  if(figure) {
    figure->draw();
  }
}
