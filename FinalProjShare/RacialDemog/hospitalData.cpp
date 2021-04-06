#include "hospitalData.h"
#include "visitor.h"
#include <sstream>


/* print hospital data partial - you must fill in*/
std::ostream& operator<<(std::ostream &out, const hospitalData &HD) {
//    out << "Hospital Info: " << HD.name << ", " << HD.state;
//    out << "\nType: " << HD.type;
    out << "\nOverall rating (out of 5): " << HD.overallRate;
    out << "\nmortality rating: " << HD.mortality;
    out << "\nreadmission rating:" << HD.readmit;
    return out;
}

void hospitalData::accept(class Visitor &v){
    v.visit(shared_from_this());
}
