#ifndef _VEC2_
#define _VEC2_

#include "util.h"

#include <iostream>

struct vec2 {

  vec2();
  vec2( float _x, float _y);
  vec2( const vec2& other);
  vec2 operator= ( const vec2& rhs);
  ~vec2();

  float x;
  float y;

  vec2 operator+ ( const vec2& rhs) const;
  vec2 operator+= ( const vec2& rhs);
  vec2 operator- ( const vec2& rhs) const;
  vec2 operator-= ( const vec2& rhs);

  vec2 operator* ( float rhs) const;
  vec2 operator*= ( float rhs);

  operator float() const;
  float lengthSquared() const;

  vec2 normalize();
  vec2 normalized() const;

  static float dot( const vec2& lhs, const vec2& rhs);

  friend std::ostream& operator << (std::ostream& os, const vec2& vec);
};

std::ostream& operator << (std::ostream& os, const vec2& vec);

#endif //_VEC2_
