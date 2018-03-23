#ifndef _COIN_
#define _COIN_

#include "figure.h"

class Coin : public Figure {
public:
  void draw(vec2 position) const {
    glColor3ub( 179, 153, 0);
    glBegin(GL_POLYGON);
    for( unsigned i = 0; i < 6 ; ++i) {
      vec2 corner = getHexCorner(i) * 0.3f + position;
      glVertex2f( corner.x, corner.y);
    }
    glEnd();
    glColor3ub( 204, 179, 0);
    position += vec2( 0, 0.1f);
    glBegin(GL_POLYGON);
    for( unsigned i = 0; i < 6 ; ++i) {
      vec2 corner = getHexCorner(i) * 0.3f + position;
      glVertex2f( corner.x, corner.y);
    }
    glEnd();
    glColor3ub( 179, 153, 0);
    glBegin(GL_POLYGON);
    for( unsigned i = 0; i < 3 ; ++i) {
      vec2 corner = getHexCorner(i) * 0.2f + position;
      glVertex2f( corner.x, corner.y);
    }
    for( int i = 2; i >= 0; --i) {
      vec2 corner = getHexCorner(i) * 0.2f + position + vec2( 0, -0.1f);
      glVertex2f( corner.x, corner.y);
    }
    glEnd();
    glColor3ub( 192, 160, 0);
    glBegin(GL_POLYGON);
    for( unsigned i = 0; i < 3 ; ++i) {
      vec2 corner = getHexCorner(i) * 0.2f + position + vec2( 0, -0.1f);
      glVertex2f( corner.x, corner.y);
    }
    for( unsigned i = 3; i < 6; ++i) {
      vec2 corner = getHexCorner(i) * 0.2f + position;
      glVertex2f( corner.x, corner.y);
    }
    glEnd();
  };
};

#endif
