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
    cityHospitalData(string inName, string inCity, string inState, string inType, int inRating,
        rating inMort, rating inReAdmit) : hospitalData{ inState, inRating, inMort, inReAdmit}, 
        city(inCity), type(inType), hospitalName(inName) {
    }

    string getCity() const {return city; }
    string getType() const { return type; }
    string getHospName() const { return hospitalName; }

   friend std::ostream& operator<<(std::ostream &out, const cityHospitalData &HD) {
    out << "City: " << HD.getCity() << " Type: " << HD.getType();
    out  << " name: " << HD.getHospName();
    out << (hospitalData)HD;
    return out;
   }

private:
    const string city;
    const string type;
    const string hospitalName;
};

#endif
