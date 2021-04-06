#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "hospitalData.h"
#include "cityHospitalData.h"
#include "demogData.h"
#include "countyDemogData.h"
#include "visitor.h"
#include "parse.h"
#include "housingData.h"
#include <memory>
#include <fstream>

class visitorCombineCounty : public Visitor {
    public: 
    visitorCombineCounty(string filename) {
        read_csvCityCounty(filename); 
    }
    
    void read_csvCityCounty(std::string filename) {
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

            }
            // Close file
            myFile.close();
        }
    }
    virtual void visit(placeData *p) {
        if(dynamic_cast<cityHospitalData*>(p)) {
            cityHospitalData* hosp = static_cast<cityHospitalData*>(p);
            string city = hosp->getCity();
            string state = hosp->getState();
            string cityKey = city+state;
            string countyName = cityToCounty[cityKey]+" County"+state;
            // if first county entry, create it
            if (allCountyHData.count(countyName) < 1) {
            allCountyHData[countyName] = new comboHospitalData("County", state, countyName);
            } 
            // either way add hospital data to the county
            allCountyHData[countyName]->addHospitaltoRegion(hosp);
        } else if (dynamic_cast<housingData*>(p)){
            housingData* h = static_cast<housingData*>(p);
            string countyName = h->getCounty()+h->getState();
            allCountyHousingData[countyName] = h;
        }else {
            countyDemogData* d = static_cast<countyDemogData*>(p);
            string countyName = d->getCounty()+d->getState();
            allCountyDData[countyName] = d;
        }
    }

    std::map<string, countyDemogData*> countyDmap() {return allCountyDData;}
    countyDemogData* countyDmapEntry(string countyN)  {return allCountyDData[countyN];}

    std::map<string, housingData*> countyHousemap() {return allCountyHousingData;}
    housingData* countyHousemapEntry(string countyN)  {return allCountyHousingData[countyN];}

    std::map<string, comboHospitalData*> countyHmap() const {return allCountyHData;}
    comboHospitalData* countyHmapEntry(string countyN) {return allCountyHData[countyN];}
  
private:
        //map for county hospital data
        std::map<string, comboHospitalData*> allCountyHData;
        //map for county name to demog data
        std::map<string, countyDemogData*> allCountyDData;

        std::map<string, housingData*> allCountyHousingData;
        

        //helper map to create aggregates from city -> county
        std::map<string, string> cityToCounty;
};

#endif
