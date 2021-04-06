#include "hospitalData.h"
#include <sstream>
#include "visitor.h"
#include <iomanip>
#include "string"

void hospitalData::accept(class Visitor &v){
        v.visit(this);
}

/* print hospital data */
std::ostream& operator<<(std::ostream &out, const hospitalData &HD) {
    out << "\nHospital Info: " << HD.place;
   // out << "\nType: " << HD.type;
   out << std::setprecision(2) << std::fixed;
    out << "\nOverall rating (out of 5): " << HD.overallRate;
    //out << "\nmortality rating: " << HD.mortRate ;
    //out << "\nreadmission rating:" << HD.readmitRate << endl;
    return out;
}
