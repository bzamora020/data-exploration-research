#include "hospitalData.h"
#include "visitor.h"
//#include <sstream>

/* print hospital data */

/*
std::ostream& operator<<(std::ostream &out, const hospitalData &HD) {
  out << "Hosptial Info: " << HD.getRegion();
//  out << "\nType: " << HD.type;
  out << "\nOverall rating (out of 5): " << HD.overall;
  out << "\nmortality rating: " << HD.mortality;
  out << "\nreadmission rating:" << HD.readmission;
  return out;
}
*/

void hospitalData::accept(class Visitor &v){
  v.visit(this);
}
