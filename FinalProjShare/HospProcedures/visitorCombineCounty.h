#ifndef VCOMBOC_H
#define VCOMBOC_H

#include <memory>
#include <fstream>
#include <string>
#include <map>

#include "hospitalData.h"
#include "cityHospitalData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "visitor.h"
#include "parse.h"



class visitorCombineCounty : public Visitor {
  public:
    visitorCombineCounty(string filename) { read_csvCityCounty(filename); }
    // CAREFUL, destructor for allCountyDData handled by external containers!!!
    ~visitorCombineCounty(){

      for (auto key : allCountyHData){
        delete key.second;
      }
    }
    std::map<string, countyDemogData*> countyDmap() { return allCountyDData; }
    countyDemogData* countyDmapEntry(string countyN) {
      if (allCountyDData.count(countyN) < 1){
        return NULL;
      } else {
        return allCountyDData[countyN];
      }
    }

    std::map<string, comboHospitalData*> countyHmap() { return allCountyHData; }
    comboHospitalData* countyHmapEntry(string countyN) {
      if (allCountyHData.count(countyN) < 1){
        return NULL;
      } else {
        return allCountyHData[countyN];
      }
    }


     void visit(demogData* e) {
       countyDemogData* tempD = (countyDemogData*) e;
       std::size_t found = (tempD->getName()).find("County");
       string county = "";
       if (found!=std::string::npos){
        county = tempD->getName() + e->getRegion();
       } else {
         county = tempD->getName() + " County" + e->getRegion();
       }


       if (allCountyDData.count(county) < 1) {

          allCountyDData[county] = tempD;
       }

     }

     void visit(hospitalData* e) {

       string state = e->getRegion();

       cityHospitalData* tempH = (cityHospitalData*) e;
       //create a key to find the corresponding county
       string cityKey = (tempH->getCity()) + (e->getRegion()); //city + state
       string county = cityToCounty[cityKey] + " County" + state; //

       //if first county entry, create it
       if (allCountyHData.count(county) < 1) {
          //cout << "Making a new county entry: " << county << endl;
          allCountyHData[county] = new comboHospitalData(county);
       }


       //this keeps a running total
       allCountyHData[county]->addHospitaltoRegion(e);

     }


     void updateRatings() {
       for (auto &i : allCountyHData){
         i.second->updateRegionRatings();
       }
     }


  private:
    //county maps
    std::map<string, countyDemogData*> allCountyDData; //points to external locations
    std::map<string, comboHospitalData*> allCountyHData;
    std::map<string, string> cityToCounty;

    //helper functions
    void read_csvCityCounty(std::string filename){

        // Create an input filestream
        std::ifstream myFile(filename);

        // Make sure the file is open
        if(!myFile.is_open()) {
            throw std::runtime_error("Could not open file");
        }

        if(myFile.good()) {
            consumeColumnNames(myFile);

            // Helper vars
            std::string line, state, junk;

            // Now read data, line by line and enter into the map
            while(std::getline(myFile, line)) {

              std::stringstream ss(line);

              string city = getFieldNQ(ss);
              state = getFieldNQ(ss);
              junk = getFieldNQ(ss);
              string county = getFieldNQ(ss);

              string cityKey = city+state;

              cityToCounty[cityKey] = county;

              //cout << "line: " << line << endl;
              //cout << "pair (city, county): " << city << ", " << county << " state " << junk << endl;
            }

            // Close file
            myFile.close();
        }
    }

};

#endif
