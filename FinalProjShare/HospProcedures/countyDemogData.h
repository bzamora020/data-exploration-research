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
    countyDemogData(string inN, string inR, int in65, int in18,
        int in5, int inBA, int inHS, int belowPov, int totalPop14) :
            demogData(inR, in65, in18, in5, inBA, inHS, belowPov, totalPop14),
            name(inN) {}

    string getName() { return name; }


  private:
    const string name;
};

#endif
