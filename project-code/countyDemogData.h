#ifndef CDEMOG_H
#define CDEMOG_H

#include <string>
#include <iostream>
#include "demogData.h"

using namespace std;

/*
  county demographic data used to represent the CORGIS data
*/
class countyDemogData : public demogData {
  public:
    countyDemogData(string inN, string inS, double in65, double in18,
        double in5, double inBA, double inHS,
        double belowPov, int totalPop14, RacialData rIn) : demogData{inS, in65, in18,
            in5, inBA, inHS, belowPov, totalPop14, rIn},
            countyName(inN) {}

    string getCounty() const { return countyName; }

    friend std::ostream& operator<<(std::ostream &out, const countyDemogData &DI) {
        out << "County: " << DI.getCounty() <<"\n";
        //call on parent output
        out << (demogData)DI;
        return out;
    }

private:
    const string countyName;

};
#endif
