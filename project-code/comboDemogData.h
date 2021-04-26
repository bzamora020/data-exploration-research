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
    comboDemogData(string inRegType, string inS) : demogData{inS},
            numCombined(0), region(inRegType)  {}

  int getNumCombined() const { return numCombined; } 
  string getRegionType() const { return region; } 

  void addDemogtoRegion(demogData *DD);

  friend std::ostream& operator<<(std::ostream &out, const comboDemogData &DI) {
        out << "Combined data at level: " << DI.getRegionType();
        cout << " includes num subregions: " << DI.getNumCombined() <<"\n";
        //call on parent output
        out << (demogData)DI;
        return out;
  }

private:
    int numCombined;
    string region; //either state or could be larger region 'southwest'
};
#endif
