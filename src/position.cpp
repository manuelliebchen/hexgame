#include "position.h"

std::ostream& operator<< (std::ostream& os, const Position& position) {
  os << "Postition: " << position.x << ", " << position.y;
  return os;
}
