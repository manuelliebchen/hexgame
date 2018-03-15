#ifndef _BUSH_
#define _BUSH_

#include "figure.h"

class Bush : public Figure {
public:
  void draw(vec2 position){
    glColor3f( (73)/256.0f, (28)/256.0f, (11)/256.0f);
    glBegin(GL_POLYGON);
      for( int i = 0; i < 6; ++i) {
        glVertex( getHexCorner(i) * 0.15f + position);
      }
    glEnd();
    glColor3f( (25)/256.0f, (71)/256.0f, (7)/256.0f);
    glBegin(GL_POLYGON);
      for( int i = 0; i < 6; ++i) {
        vec2 corner = getHexCorner(i) * 0.3f + position;
        glVertex2f( corner.x, corner.y + 0.2f);
      }
    glEnd();
    glColor3f( (35)/256.0f, (81)/256.0f, (17)/256.0f);
    glBegin(GL_POLYGON);
      for( int i = 0; i < 6; ++i) {
        vec2 corner = getHexCorner(i) * 0.2f + position;
        glVertex2f( corner.x, corner.y + 0.2f);
      }
    glEnd();
  };
};

#endif
