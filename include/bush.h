#ifndef _BUSH_
#define _BUSH_

#include "figure.h"

class Bush : public Figure {
public:
  void draw(vec2 position){
    glColor3ub( 73, 28, 11);
    glBegin(GL_POLYGON);
      for( int i = 0; i < 6; ++i) {
        glVertex( getHexCorner(i) * 0.15f + position);
      }
    glEnd();
    glColor3ub( 25, 71, 7);
    glBegin(GL_POLYGON);
      for( int i = 0; i < 6; ++i) {
        vec2 corner = getHexCorner(i) * 0.3f + position;
        glVertex2f( corner.x, corner.y + 0.2f);
      }
    glEnd();
    glColor3ub( 35, 81, 17);
    glBegin(GL_POLYGON);
      for( int i = 0; i < 6; ++i) {
        vec2 corner = getHexCorner(i) * 0.2f + position;
        glVertex2f( corner.x, corner.y + 0.2f);
      }
    glEnd();
  };
};

#endif
