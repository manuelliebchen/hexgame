#ifndef _POSITION_
#define _POSITION_

#include <iostream>

struct Position {
  int x;
  int y;

  Position() {
    x = 0;
    y = 0;
  };

  Position( int _x, int _y) {
    x = _x;
    y = _y;
  };

  Position( const Position& pos) {
    x = pos.x;
    y = pos.y;
  };

  bool operator== ( const Position& pos) const {
    return x == pos.x && y == pos.y;
  }

  bool operator!= ( const Position& pos) const {
    return !((*this) == pos);
  }

  bool operator< ( const Position& pos) const {
    return x < pos.x && y < pos.y;
  }

  friend std::ostream& operator<< (std::ostream& os, const Position& position);
};
#endif
