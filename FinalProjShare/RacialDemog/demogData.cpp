#include "demogData.h"
#include "visitor.h"
#include <sstream>

/* print county demographic data */
std::ostream& operator<<(std::ostream &out, const demogData &DD) {
    out << "County Demographics Info: " << DD.getState();
    out << "\nPopulation info: \n(\% over 65): " << DD.getpopOver65() * 100.0f;
    // out <<  " Count: " << DD.getpopOver65Count();
    out << "\n(\% under 18): " << DD.getpopUnder18() * 100.0f;
    // out <<  " Count: " << DD.getpopUnder18Count();
    out << "\n(\% under 5): " << DD.getpopUnder5() * 100.0f;
    // out <<  " Count: " << DD.getpopUnder5Count();
    out << "\nEducation info: \n(\% Bachelor degree or more): " << DD.getBAup() * 100.0f;
    // out <<  " Count: " << DD.getBAupCount();
    out << "\n(\% high school or more): " << DD.getHSup() * 100.0f;
    // out <<  " Count: " << DD.getHSupCount();
    out << "\n\% below poverty: " << DD.getBelowPoverty() * 100.0f;
    // out <<  " Count: " << DD.getBelowPovertyCount();
    out << "\nTotal population: " << DD.population2014;
    return out;
}

void demogData::accept(class Visitor &v){
    v.visit(shared_from_this());
}
