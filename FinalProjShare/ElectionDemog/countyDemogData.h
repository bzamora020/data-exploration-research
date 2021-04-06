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
    countyDemogData(string c, string inS, double in65, double in18,
        double in5, double tPop) : demogData("", inS, in65, in18,
            in5, tPop), county(c) {}
    string getCounty() { return county; }
private:
    string county;
};
#endif
