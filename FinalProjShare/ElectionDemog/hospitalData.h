#ifndef HOSP_H
#define HOSP_H

#include <string>
#include <iostream>
#include <utility>
#include "rating.h"
#include "placeData.h"

using namespace std;

/*
  class to represent hospital data
  from CORGIS
*/
class hospitalData : public placeData{
  public:
	 //constructor for starting code - make complete by adding rating
    hospitalData(string inN, string inC, string inS, string inType) :
            placeData(inN), city(inC), state(inS), type(inType), overallrate(0), mortality(), readmit() {}
    hospitalData(string inN, string inC, string inS, string inType, double o, rating m, rating r) :
            placeData(inN), city(inC), state(inS), type(inType), overallrate(o), mortality(m), readmit(r){}
    hospitalData(hospitalData& h) : placeData(h.getName()), state(h.state), type(h.type), overallrate(h.overallrate), mortality(h.mortality), readmit(h.readmit) {}
    hospitalData(string inS) : placeData(), state(inS), type(""), overallrate(0), mortality(0), readmit(0) {}
    
    string getCity() const { return city; }
    string getState() const { return state; }
    string getType() const { return type; }
    double getOverallRate() const { return overallrate; }
    rating getMortality() { return mortality; }
    rating getReadmit() { return readmit; }

    void setOverallRate(double i) { overallrate = i; }
    void setMortality(rating r) { mortality = r; }
    void setReadmit(rating r) { readmit = r; }

    static bool compareOV(hospitalData* ph1, hospitalData* ph2) {
        if (ph1->overallrate == ph2->overallrate)
            return ph1->getName().compare(ph2->getName());
        return ph1->overallrate < ph2->overallrate;
    }

    friend ostream& operator<<(ostream &out, hospitalData &HD);

    void accept(class Visitor& v);
private:
    string city;
    string state;
    string type;
    double overallrate;
    rating mortality;
    rating readmit;

};

#endif
