#ifndef COMBOD_H
#define COMBOD_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "placeData.h"

/*
  aggregated demographic data for a given regional level (state - or larger region)
*/
class comboDemogData : public demogData  {
  public:
    comboDemogData(string inRT, string inS) :
            demogData{inS, 0, 0,
            0, 0, 0,
            0, 0}, region(inS), regionType(inRT), numCounties(0) {}
    // if region is different from highest level name
    comboDemogData(string inRT, string inS, string inN) :
            demogData{inS, 0, 0,
            0, 0, 0,
            0, 0}, region(inN), regionType(inRT), numCounties(0) {}

  int getNumC() const { return numCounties; }
  string getRegion() const {return region;}
  string getRegionType() const {return regionType;}
  string getName() const {return place;}

  friend std::ostream& operator<<(std::ostream &out, const comboDemogData &SD);
  void addDemogtoRegion(demogData* CD);
  
private:
    string region;
    string regionType;
    int numCounties;
};
#endif
