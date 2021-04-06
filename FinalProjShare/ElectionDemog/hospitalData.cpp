#include "hospitalData.h"
#include "visitor.h"
#include <sstream>


/* print hospital data partial - you must fill in*/
std::ostream& operator<<(std::ostream& out, hospitalData& HD) {
    /*
    out << "Hosptial Info: " << HD.getName() << ", " << HD.getState();
    out << "\nType: " << HD.getType();
    out << "\nOverall rating (out of 5): " << HD.getOverallRate();
    out << "\nmortality rating: " << HD.getMortality().getRating();
    out << "\nreadmission rating:" << HD.getReadmit().getRating();
    */
    //out << HD.getName() << ", " << HD.getType() << ", " <<  HD.getOverallRate() << ", " <<  HD.getMortality() << ", " <<  HD.getReadmit();
    out << "Hosptial Info: " << HD.getName();
    out << "\nOverall rating (out of 5): " << HD.getOverallRate();
    out << "\nOverall rating (out of 5): " << HD.getOverallRate();
    return out;
}

void hospitalData::accept(class Visitor& v) { v.visit(this); }