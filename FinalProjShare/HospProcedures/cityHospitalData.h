#ifndef CITYHOSP_H
#define CITYHOSP_H

#include <string>
#include <iostream>
#include <utility>
#include "rating.h"

using namespace std;

/*
  city hospital data for specifics of CORGIS data
*/
class cityHospitalData : public hospitalData   {
  public:
    cityHospitalData(string inN, string inC, string inR, string inT,
      double inOv, string inMor, string inRea, string inHAQ, string inHAV,
      string inHFQ, string inHFV, string inPQ) :
        hospitalData(inR, inOv, inMor, inRea, inHAQ, inHAV, inHFQ, inHFV, inPQ),
        name(inN), city(inC), type(inT) {}

    string getName() const { return name; }
    string getCity() const { return city; }
    string getType() const { return type; }

  private:
    const string name;
    const string city;
    const string type;
    //state in placeData - aka the larger region, which would be the state
};

#endif
