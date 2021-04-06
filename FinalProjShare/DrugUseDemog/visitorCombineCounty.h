#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "hospitalData.h"
#include "cityHospitalData.h"
#include "demogData.h"
#include "countyDemogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"


#include "visitor.h"
#include "parse.h"
#include <algorithm>
#include <memory>
#include <fstream>


class visitorCombineCounty : public Visitor {
    public:
    
        

        visitorCombineCounty(std::string csvFileName) {
            read_csvCityCounty(csvFileName);   
        }

        void visit(std::shared_ptr<hospitalData> hosp2) override {
            
            std::shared_ptr<cityHospitalData> hosp = std::dynamic_pointer_cast<cityHospitalData>(hosp2);

            string cityName = hosp->getCity();
            string stateName = hosp->getState();
            string countyName = cityToCounty[cityName + stateName];

            if (countyName == "") {
                cout << "";
            }

            if (allCountyHData.count(countyName + stateName) < 1) {
                //cout << "Making a new hospital entry: " << countyName << endl;
                allCountyHData[countyName + stateName] = new comboHospitalData(countyName, countyName, stateName);
            }
            //either way now add this county info 
            //this keeps a running total
            allCountyHData[countyName + stateName]->addHospitaltoRegion(hosp);
        }

        void visit(demogData &demog) override{
            string countyName = demog.getName();
            string stateName = demog.getState();

            size_t found = countyName.find(" County");
            
            if (countyName.find(" County")!=string::npos)
                countyName.erase(found, 7);


            if(allCountyDData.count(countyName) < 1){
                allCountyDData[countyName + stateName] = new comboDemogData(countyName, countyName, stateName);
            }
            allCountyDData[countyName + stateName]->addDemogtoRegion(make_shared<demogData>(demog));

        }


        // demog getters
        std::map<string, comboDemogData*> countyDmap() { return allCountyDData; }
        comboDemogData* countyDmapEntry(string countyN) { return allCountyDData[countyN]; }

        // hosp getters
        std::map<string, comboHospitalData*> countyHmap() { return allCountyHData; }
        comboHospitalData* countyHmapEntry(string countyN) { return allCountyHData[countyN]; }

        // city to County csv file (from dataAQ)
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

                        //cout << "line: " << line << endl;
                        //cout << "pair (city, county): " << city << ", " << county << " state " << junk << endl;
                    }

                    // Close file
                    myFile.close();
            }
        }

        private:
        //map for county hospital data
        std::map<string, comboHospitalData*> allCountyHData;
        //map for county name to demog data
        std::map<string, comboDemogData*> allCountyDData;

        //helper map to create aggregates from city -> county
        std::map<string, string> cityToCounty;


};

#endif
