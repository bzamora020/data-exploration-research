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

    countyDemogData(string inN, string inS, int in65, int in18,
        int in5, int inBA, int inHS, int belowPov, int totalPop14) : demogData(inN, inS, "county", in65, in18, in5, inBA, inHS, belowPov, totalPop14) {}

};
#endif
