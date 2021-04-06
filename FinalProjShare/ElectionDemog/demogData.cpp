#include "demogData.h"
#include "visitor.h"
#include <sstream>

/* print county demographic data */
std::ostream& operator<<(std::ostream &out, demogData &DD) {
    /*
    out << "County Demographics Info: " << DD.getName()<< ", " << DD.getState();
    out << "\nPopulation info: \n(\% over 65): " << DD.getpopOver65();
    out << "\n(\% under 18): " << DD.getpopUnder18();
    out << "\n(\% under 5): " << DD.getpopUnder5();
    out << "\nEducation info: \n(\% Bachelor degree or more): " << DD.getBAup();
    out << "\n(\% high school or more): " << DD.getHSup();
    out << "\nTotal Population: " << DD.getTotalPop();
    out << "\nProportion under the poverty line: " << DD.getBelowPoverty();
    */
    //out  << DD.getName() << ", " << DD.getState() << ", " << DD.getTotalPop();
    out << "Demographics Info(State) : " << DD.getState();
    out << "\nEducation info :";
    out << "\n(% bachelor degree or more) : " << DD.getBAup();
    out << "\n(% high school or more) : " << DD.getHSup();
    out << "\n% below poverty : " << DD.getBelowPoverty();
    return out;
}

void demogData::accept(class Visitor& v) { v.visit(this); }
