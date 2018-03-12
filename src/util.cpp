#include "util.h"

float randf() {
  std::random_device rd;
  std::uniform_real_distribution<float> dist( 0,1);
  return dist(rd);
};

vec2 getHexCorner( int n){
  n %= 6;
  switch( n) {
    case 0: return vec2( three_sqrt_half, 0.5f);
    case 1: return vec2( 0, 1);
    case 2: return vec2( -three_sqrt_half, 0.5f);
    case 3: return vec2( -three_sqrt_half, -0.5f);
    case 4: return vec2( 0, -1);
    default: return vec2( three_sqrt_half, -0.5f);
  }
}

void glVertex(vec2 vector) {
  glVertex2f( vector.x, vector.y);
}
