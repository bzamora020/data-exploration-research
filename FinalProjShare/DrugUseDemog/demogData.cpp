
#include "demogData.h"

#include "visitor.h"

ostream& operator<<(ostream &out, const demogData &DD) {
        out << "Demographics Info: " << DD.name << ", " << DD.state;
        out << "\nPopulation info: \n(\% over 65): " << DD.getpopOver65();
        out <<  " Count: " << DD.getpopOver65Count();
        out << "\n(\% under 18): " << DD.getpopUnder18();
        out <<  " Count: " << DD.getpopUnder18Count();
        out << "\n(\% under 5): " << DD.getpopUnder5();
        out <<  " Count: " << DD.getpopUnder5Count();
        out << "\nEducation info: \n(\% Bachelor degree or more): " << DD.getBAup();
        out <<  " Count: " << DD.getBAupCount();
        out << "\n(\% high school or more): " << DD.getHSup();
        out <<  " Count: " << DD.getHSupCount();
        out << "\n\% below poverty: " << DD.getBelowPoverty();
        out <<  " Count: " << DD.getBelowPovertyCount();
        out << "\nTotal population: " << DD.population2014;
        return out;
}

 void demogData::accept(class Visitor &v) {
         v.visit(*this);
 }