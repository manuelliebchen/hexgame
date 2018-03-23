#include "player.h"

void
Player::draw( vec2 position) const {
  glColor3ub( 160, 3, 3);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i) * 0.3f + position;
    glVertex2f( corner.x, corner.y);
  }
  glEnd();
  glColor3ub( 232, 44, 11);
  position += vec2( 0, 0.1f);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i) * 0.3f + position;
    glVertex2f( corner.x, corner.y);
  }
  glEnd();
  glColor3ub(200, 20, 5);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i) * 0.2f + position;
    glVertex2f( corner.x, corner.y);
  }
  glEnd();
  position += vec2( 0, 0.2f);
  glColor3ub( 242, 54, 21);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i) * 0.2f + position;
    glVertex2f( corner.x, corner.y);
  }
  glEnd();
}
