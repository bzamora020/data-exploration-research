#ifndef CITYHOSP_H
#define CITYHOSP_H

#include <string>
#include <iostream>
#include <utility>
#include "rating.h"
#include "hospitalData.h"

using namespace std;

/*
  city hospital data for specifics of CORGIS data
*/
class cityHospitalData : public hospitalData   {
public:
  cityHospitalData(string inN, string inS, string inC, string inType, int inOR, rating inMR, rating inRR) :
    hospitalData{inS, inOR, inMR, inRR}, hospName(inN), type(inType), city(inC)  {}
    string getCity() const { return city; }
    string getHospName () const {return hospName;}
    string getType() const {return type;}

    
private:
  const string hospName;
  const string type;
  const string city;
};

#endif
