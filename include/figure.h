#ifndef _FIGURE_
#define _FIGURE_

#include <GL/glut.h>
#include "util.h"

class Figure {

public:
  void draw();
};

inline
void
Figure::draw() {
  glPushMatrix();
  glColor3f( 0.7f, 0.6f, 0);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i);
    glVertex2f( corner.x * 0.3f, corner.y * 0.3f);
  }
  glEnd();
  glColor3f( 0.8f, 0.7f, 0);
  glTranslatef( 0, 0.1f, 0);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 6 ; ++i) {
    vec2 corner = getHexCorner(i);
    glVertex( corner * 0.3f);
  }
  glEnd();
  glColor3f( 0.7f, 0.6f, 0);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 3 ; ++i) {
    vec2 corner = getHexCorner(i);
    glVertex2f( corner.x * 0.2f, corner.y * 0.2f);
  }
  for( int i = 2; i >= 0; --i) {
    vec2 corner = getHexCorner(i);
    glVertex2f( corner.x * 0.2f, corner.y * 0.2f - 0.1f);
  }
  glEnd();
  glColor3f( 0.75f, 0.65f, 0);
  glBegin(GL_POLYGON);
  for( unsigned i = 0; i < 3 ; ++i) {
    vec2 corner = getHexCorner(i);
    glVertex2f( corner.x * 0.2f, corner.y * 0.2f - 0.1f);
  }
  for( unsigned i = 3; i < 6; ++i) {
    vec2 corner = getHexCorner(i);
    glVertex2f( corner.x * 0.2f, corner.y * 0.2f);
  }
  glEnd();
  glPopMatrix();
};

#endif
