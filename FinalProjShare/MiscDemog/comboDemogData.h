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
  double getMeanCommute() { return misc.getMeanCommute()/numCombined; } 
  string getRegionType() const { return region; } 

  void addDemogtoRegion(demogData*  DD);

  friend std::ostream& operator<<(std::ostream &out, const comboDemogData &DI) {
        out << "Combined data at level: " << DI.getRegionType();
        cout << " includes num subregions: " << DI.getNumCombined() <<"\n";
        //call on parent output
        out << (demogData)DI;
        return out;
  }

  void printMisc() { 
        cout << "\tPlace Name: " << this->getName() << endl;
        cout << "Building Permits: " << misc.getBuildingPerm() << endl;
        cout << "Percent Foreign Born: " << this->getPopForeign() << "%" << endl;
        cout << "Land Area (square miles): " << misc.getLandArea() << endl;
        cout << "Percent Language Other than English at Home: " << this->getPopOtherLang() << "%" << endl;
        cout << "Percent Same House: " << this->getPopSameHouse() << "%" << endl;
        cout << "Number of Manufacturers Shipments: " << misc.getManufacturerShipments() << endl;
        cout << "Mean Travel Time to Work (minutes): " << this->getMeanCommute() << endl;
        cout << "Percent Female: " << this->getPopFemale() << "%" << endl;
        cout << "Number of Veterans: " << misc.getVeterans() << endl;
        cout << endl;
  }

private:
    int numCombined;
    string region; //either state or could be larger region 'southwest'
};
#endif
