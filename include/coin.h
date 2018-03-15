#ifndef _COIN_
#define _COIN_

#include "figure.h"

class Coin : public Figure {
public:
  void draw(vec2 position) {
    glPushMatrix();
    glColor3ub( 179, 153, 0);
    glBegin(GL_POLYGON);
    for( unsigned i = 0; i < 6 ; ++i) {
      vec2 corner = getHexCorner(i) + position;
      glVertex2f( corner.x * 0.3f, corner.y * 0.3f);
    }
    glEnd();
    glColor3ub( 204, 179, 0);
    glTranslatef( 0, 0.1f, 0);
    glBegin(GL_POLYGON);
    for( unsigned i = 0; i < 6 ; ++i) {
      vec2 corner = getHexCorner(i) + position;
      glVertex( corner * 0.3f);
    }
    glEnd();
    glColor3ub( 179, 153, 0);
    glBegin(GL_POLYGON);
    for( unsigned i = 0; i < 3 ; ++i) {
      vec2 corner = getHexCorner(i) + position;
      glVertex2f( corner.x * 0.2f, corner.y * 0.2f);
    }
    for( int i = 2; i >= 0; --i) {
      vec2 corner = getHexCorner(i) + position;
      glVertex2f( corner.x * 0.2f, corner.y * 0.2f - 0.1f);
    }
    glEnd();
    glColor3ub( 192, 160, 0);
    glBegin(GL_POLYGON);
    for( unsigned i = 0; i < 3 ; ++i) {
      vec2 corner = getHexCorner(i) + position;
      glVertex2f( corner.x * 0.2f, corner.y * 0.2f - 0.1f);
    }
    for( unsigned i = 3; i < 6; ++i) {
      vec2 corner = getHexCorner(i) + position;
      glVertex2f( corner.x * 0.2f, corner.y * 0.2f);
    }
    glEnd();
    glPopMatrix();
  };
};

#endif
