#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "cityHospitalData.h"
#include "countyDemogData.h"
#include "demogData.h"
#include "hospitalData.h"
#include "parse.h"
#include "visitor.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include <string>


class visitorCombineCounty : public Visitor {

public:
  visitorCombineCounty(string fileName) // Creates helper map when instantiated
                                        // with the uscities file
  {
    // Create an input filestream
    std::ifstream myFile(fileName);

    // Make sure the file is open
    if (!myFile.is_open()) {
      throw std::runtime_error("Could not open file");
    }

    if (myFile.good()) {
      consumeColumnNames(myFile);

      // Helper vars
      std::string line;

      // Now read data, line by line and enter into the map
      while (std::getline(myFile, line)) {

        std::stringstream ss(line);
        // First csv
        string city = getFieldNQ(ss);
        string state = getFieldNQ(ss);
        string junk = getFieldNQ(ss);
        string county = getFieldNQ(ss);

        string cityKey = city + state;

        cityToCounty[cityKey] = county;
      }

      // Close file
      myFile.close();
    }
  }

  void visit(hospitalData *e) {

    if (e) {
      string city = ((cityHospitalData *)e)->getCity();
      // city names can be redundent
      string cityKey = city + e->getState();
      string county = "";
      string countyKey = "";
      // figure out the county
      if (cityToCounty.count(cityKey) >= 1) {
        county = cityToCounty[cityKey];
      } else {
        county = "unknown " + e->getState();
      }

      countyKey = county + e->getState();

      // if first county entry, create it
      if (allCountyHData.count(countyKey) < 1) {

        allCountyHData[countyKey] =
            new comboHospitalData(county + " County", e->getState());
      }
      // either way now add this city hospital to the right county
      comboHospitalData *ce = allCountyHData[countyKey];
      if (ce) {
        ce->addHospitaltoRegion(e);
      }
    }
  }

  void visit(demogData *e) {
    if (e) {
      string countyName = ((countyDemogData *)e)->getCounty();

      string test = countyName;

      size_t found = test.find(" County");

      if (test.find(" County") != string::npos) {
        test.erase(found, 7);
      }

      string countyKey = test + e->getState();

      // if first state entry, create it

      if (allCountyDData.count(countyKey) < 1) {
        // cout << "Making a new county entry: " << countyName << endl;
        allCountyDData[countyKey] =
            new comboDemogData(countyName, e->getState());
      }
      // either way now add this county info
      // this keeps a running total
      comboDemogData *ce = allCountyDData[countyKey];
      if (ce) {
        ce->addDemogtoRegion(e);
      }
    }
  }
  int unkCounter = 0;

  void visit(shootingData *e) {
    if (e) {
      string county = ((cityShootingData *)e)->getCity();

      string countyKey = "";
      string test = county;
      size_t found = test.find(" County");
      if (county.find(" County") != std::string::npos) {
        test.erase(found, 7);
        county = test;
      } else {
        unkCounter++;
        county = "Unknown";
      }

      countyKey = county + e->getState();

      // if first county entry, create it
      if (allCountySData.count(countyKey) < 1) {

        allCountySData[countyKey] =
            new comboShootingData(county + " County", e->getState());
      }

      // either way now add this city's shooting incident to the right county
      comboShootingData *cs = allCountySData[countyKey];
      if (cs) {
        cs->addShootingtoRegion(e);
      }
    }
  }

  std::map<string, comboDemogData *> countyDmap() { return allCountyDData; }

  comboDemogData *countyDmapEntry(string countyN) {
    return allCountyDData[countyN];
  };

  std::map<string, comboHospitalData *> countyHmap() { return allCountyHData; }
  comboHospitalData *countyHmapEntry(string countyN) {
    return allCountyHData[countyN];
  }
  std::map<string, comboShootingData *> countySmap() { return allCountySData; }
  comboShootingData *countySmapEntry(string countyN) {
    return allCountySData[countyN];
  }
  
  std::string mostShootingsCounty() {
    std::vector<comboShootingData*> theCounties;
    for(const auto entry : allCountySData){
      theCounties.push_back(entry.second);
    }
    std::sort(theCounties.begin(), theCounties.end(), compareNumShootings);

    cout << "Counties with most police shootings: \n" 
         << "1.) " << theCounties[0]->getRegionType() << " in this state ->" << theCounties[0]->getState() << " had this many fatal police shootings ->" << theCounties[0]->getNumCases() << endl
         << "2.) " << theCounties[1]->getRegionType() << " in this state ->" << theCounties[0]->getState() << " had this many fatal police shootings ->" << theCounties[1]->getNumCases() << endl
         << "3.) " << theCounties[2]->getRegionType() << " in this state ->" << theCounties[0]->getState() << " had this many fatal police shootings ->" << theCounties[2]->getNumCases() << endl;
  }

private:
  // Private data like maps and stuff
  // map for county hospital data
  std::map<string, comboHospitalData *> allCountyHData;
  // map for county name to demog data
  std::map<string, comboDemogData *> allCountyDData;
  // map for county name to shooting data
  std::map<string, comboShootingData *> allCountySData;

  // helper map to create aggregates from city -> county
  std::map<string, string> cityToCounty;

  static bool compareNumShootings(comboShootingData* a, comboShootingData* b){
    return (a->getNumCases() > b->getNumCases());
  }
};

#endif
