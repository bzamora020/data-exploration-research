#include <iostream>
#include "placeData.h"

std::ostream& operator<<(std::ostream &out, const placeData &DD) {
  out << DD.name;
  return out;
}
