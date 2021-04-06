#ifndef HOUSE_H
#define HOUSE_H

#include <string>
#include <iostream>
#include <utility>
#include "placeData.h"

using namespace std;

/*
  class to represent housing data
*/
class housingData : public placeData  {
  public:
  housingData(string inC, string inS, double hO, int hh, int hu, int mv, double pph, double u) :
    placeData{inS}, county(inC), homeOwnership(hO), households(hh), housingUnits(hu),
    medianVal(mv), personsPerHouse(pph), unitsInMultiUnit(u) {}
  
  string getCounty() {return county;}
  double getHomeOwnership() const {return homeOwnership;}
  double getHouseHolds() const {return households;}
  double getHousingUnits() const {return housingUnits;}
  double getMedianVal() const {return medianVal;}
  double getPersonsPerHouse() const {return personsPerHouse;}
  double getUnitsInMultiUnit() const {return unitsInMultiUnit;}

private:
  string county;
  double homeOwnership;
  int households;
  int housingUnits;
  int medianVal;
  double personsPerHouse;
  double unitsInMultiUnit;


};

#endif
