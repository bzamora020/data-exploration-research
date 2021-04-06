#include "demogData.h"
#include <sstream>
#include "visitor.h"
#include <iomanip>
#include "string"

void demogData::accept(class Visitor &v){
        v.visit(this);
}


/* print county demographic data */
std::ostream& operator<<(std::ostream &out, const demogData &DD) {
    out << "\nDemographics Info (State): " << DD.getState(); //<< ", " << DD.getState();
    //out << "\nPopulation info: \n(\% over 65): " << DD.getpopOver65();
    //out <<  " Count: " << DD.getpopOver65Count();
    //out << "\n(\% under 18): " << DD.getpopUnder18();
    //out <<  " Count: " << DD.getpopUnder18Count();
    //out << "\n(\% under 5): " << DD.getpopUnder5();
    //out <<  " Count: " << DD.getpopUnder5Count();
    out << std::setprecision(2) << std::fixed;
    out << "\nEducation info:\n(\% Bachelor degree or more): " << DD.getBAup();
    //out <<  " Count: " << DD.getBAupCount();
    out << "\n(\% high school or more): " << DD.getHSup();
    //out <<  " Count: " << DD.getHSupCount();
    out << "\n\% below poverty: " << DD.getBelowPoverty();
    //out <<  " Count: " << DD.getBelowPovertyCount();
    //out << "\nTotal population: " << DD.population2014 << endl;
    return out;
}
