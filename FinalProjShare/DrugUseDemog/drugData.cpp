#include "drugData.h"

#include "visitor.h"

ostream& operator<<(ostream &out, const drugData &DrD) {
        out << "State Info: " << DrD.state;
        out << "\nPopulation info (18 to 25): " << DrD.getpop18to25();
        out <<  "\n Cocaine Usage Count: " << DrD.getCocaineCount();
        out <<  "\n Alchohol in the Past Month Count: " << DrD.getAlcoholCount();
        out <<  "\n Pain Relievers Abuse Count: " << DrD.getPainCount();
        out <<  "\n Marijuana Usage Count: " << DrD.getWeedCount();
        out <<  "\n Cocaine Usage per: " << DrD.getCocaine();
        out <<  "\n Alchohol in the Past Month per: " << DrD.getAlcohol();
        out <<  "\n Pain Relievers Abuse per: " << DrD.getPain();
        out <<  "\n Marijuana Usage per: " << DrD.getWeed();

        return out;
}

 void drugData::accept(class Visitor &v) {
         v.visit(*this);
 }